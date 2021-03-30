 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:17:06
 ///

#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

class Example
{
public:
	Example()
	: _number(1000)
	, _flag(true)
	, _cond(_mutex)
	{
		
	}

	void excuteTask1();

	void excuteTask2();
private:
	int _number;
	bool _flag;
	wd::MutexLock _mutex;
	wd::Condition _cond;
};

void Example::excuteTask1()
{
	int cnt = 10;
	while(cnt--) {
		wd::MutexLockGuard autolock(_mutex);//利用RAII技术保证不会发生死锁
		while(_flag == false) {
			_cond.wait();
		}
		--_number;
		//....return ....如果在这里退出 无法解锁 就会发生死锁 如果有MutexLockGuard对象 退出时调用他的析构函数 解锁操作在析构函数中进行 就可以完美的解决因为这种情况发生死锁的问题了
		printf("sub thread %ld, number = %d\n",(uint64_t)pthread_self(),_number);
		if(_flag == true) {
			_flag = false;
		}
		_cond.notify();
	}
}

void Example::excuteTask2()
{
	int cnt = 10;
	while(cnt--) {
		wd::MutexLockGuard autolock(_mutex);
		while(_flag == true) {
			_cond.wait();
		}
		--_number;
		printf("sub thread %ld, number = %d\n",(uint64_t)pthread_self(),_number);
		if(_flag == false) {
			_flag = true;
		}
		_cond.notify();
	}	
}
int main(void)
{
	printf(">>main thread starts\n");
	Example example;
	unique_ptr<wd::Thread> thread1(new wd::Thread(bind(&Example::excuteTask1,&example)));
	unique_ptr<wd::Thread> thread2(new wd::Thread(bind(&Example::excuteTask2,&example)));
	thread1->start();
	thread2->start();

	printf("main thread_id : %ld,sub thread1_id = %ld,sub thread2_id = %ld\n",(uint64_t)pthread_self(),(uint64_t)thread1->getID(),(uint64_t)thread2->getID());
	thread1->join();
	thread2->join();
	printf(">>main exit\n");
	return 0;
}
