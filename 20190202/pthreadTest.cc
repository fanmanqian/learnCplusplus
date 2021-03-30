 ///
 /// @file    pthreadTest.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-01 16:53:46
 ///
 
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;
//线程的执行在进程的空间里面
//如果当进程执行结束时，线程也无法执行
void * threadFunc(void * args)
{
	int cnt = 10;
	while(cnt--) {
		printf("sub thread %u\n",pthread_self());
		sleep(1);
	}
	return NULL;
}

int main(void)
{
	pthread_t pthid = 0;
	pthread_create(&pthid,NULL,threadFunc,NULL);//创建线程
	int cnt = 10;
	while(cnt--) {
		printf("main thread %u,sub thread %u\n",pthread_self(),pthid);//pthread_self()在线程内部查看线程id 相当于类内部的this指针
	}
	//sleep(3);
	pthread_join(pthid,NULL);//作用  等待线程pthid执行结束，阻塞(线程挂起，不再占用cpu)
	//while(1);使用死循环 还是有cpu的调度 还会占用cpu的时间片
	return 0;
}
