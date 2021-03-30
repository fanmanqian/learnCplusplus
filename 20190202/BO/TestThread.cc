 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:17:06
 ///

#include "Thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

class MyThread
{
public:
	void run()
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

void process()
{
		int cnt = 10;
		while(cnt--) {
			::srand(::clock());
			int _random = ::rand() % 100;
			cout << "sub thread : " << pthread_self() << " _random = " << _random << endl;
			sleep(1);
		}

}
void test1()
{
	MyThread task;
	wd::Thread thread(bind(&MyThread::run,&task));
	thread.start();
	thread.join();
}

void test2()
{
	wd::Thread thread(process);
	thread.start();
	thread.join();
}
int main(void)
{
	test1();
	test2();
	return 0;
}
