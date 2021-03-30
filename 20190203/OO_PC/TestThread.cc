 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:17:06
 ///

#include "Producer.h"
#include "Consumer.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

void test0()
{
	cout << ">>>main thread " << pthread_self() << " starts!\n";
	wd::TaskQueue taskqueue(10);
	unique_ptr<wd::Thread> producer(new wd::Producer(taskqueue));
	unique_ptr<wd::Thread> consumer(new wd::Consumer(taskqueue));
	producer->start();
	consumer->start();
	producer->join();
	producer->join();
}
int main(void)
{
	test0();
	return 0;
}
