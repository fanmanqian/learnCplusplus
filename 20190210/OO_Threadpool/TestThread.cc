 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 22:33:09
 ///
 
#include "Threadpool.h"
#include "Task.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <memory>
using namespace std;
using namespace wd;


class MyTask
: public wd::Task
{
public:
	//process的调用是在其中一个子线程里面完成的
	void process() override
	{
		::srand(::clock());
		int number = ::rand() % 100;
		cout << "pthid " << pthread_self() << " ,number = " << number << endl;
		::sleep(1);//代表的是该任务的执行时间是1s
	}
};

void test()
{
	unique_ptr<Task> up(new MyTask());
	unique_ptr<Threadpool> threadpoolPtr(new Threadpool(4,10));
	threadpoolPtr->start();
	int cnt = 20;
	while(cnt--) {
		threadpoolPtr->addTask(up.get());
	}
	threadpoolPtr->stop();
}

int main(void)
{
	test();
	return 0;
}
