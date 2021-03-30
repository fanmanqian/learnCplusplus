 ///
 /// @file    TestThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:17:06
 ///

#include "Producer.h"
#include "Consumer.h"
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

int main(void)
{
	printf(">>main thread starts\n");
	wd::TaskQueue taskqueue(10);
	unique_ptr<wd::Thread> producer(new wd::Thread(bind(&wd::Producer::run,wd::Producer(),std::ref(taskqueue))));
	unique_ptr<wd::Thread> consumer(new wd::Thread(bind(&wd::Consumer::run,wd::Consumer(),std::ref(taskqueue))));
	producer->start();
	consumer->start();

	//printf("main thread_id : %ld,sub producer_id = %ld,sub consumer_id = %ld\n",(uint64_t)pthread_self(),(uint64_t)thread1->getID(),(uint64_t)thread2->getID());
	producer->join();
	consumer->join();
	printf(">>main exit\n");
	return 0;
}
