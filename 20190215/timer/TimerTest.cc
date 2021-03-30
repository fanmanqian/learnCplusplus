 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:17:06
 ///

#include "Timer.h"
#include "Thread.h"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

struct Example
{
	void process()
	{
		::srand(::clock());
		int number = rand() % 100;
		cout << " number = "  << number << endl;
	}
};

int main(void)
{
	cout << "main thread start " << pthread_self() << endl;
	//定时器的含义就是第一次执行是3秒后  之后每隔5s打印一次
	wd::Timer timer(bind(&Example::process,Example()),3,5);
	wd::Thread thread(bind(&wd::Timer::start,&timer));
	thread.start();//应该让他在子线程中执行 
	cout << "start sub thread " << endl;
	cout << "main thread sleep" << endl;
	sleep(15);
	cout << "main thread wakeup" << endl;
	timer.stop();//应该让他在主线程执行
	cout << "sub thread join" << endl;
	thread.join();
	return 0;
}
