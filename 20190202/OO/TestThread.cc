 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:17:06
 ///

#include "Thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread
:public wd::Thread
{
private:
	void run()override
	{
		int cnt = 10;
		while(cnt--) {
			::srand(::clock());
			int _random = ::rand() % 100;
			cout << "sub thread : " << pthread_self() << " _random = " << _random << endl;
			sleep(1);
		}
	}
public:
	~MyThread()
	{
		cout << "~MyThread()" << endl;
	}
};

void test1()
{
	unique_ptr<wd::Thread> mypthread(new MyThread());
	mypthread->start();
	mypthread->join();
}

void test2()
{
  //这里是对象语义我们不能对其进行复制的所以我们需要Noncopyable
	MyThread mythread;
//	wd::Thread pthred(mythread)
	mythread.start();
	mythread.join();
	
	//MyThread mythread2(mythread2);//error 被禁止
}
int main(void)
{
//	test1();
	test2();
	return 0;
}
