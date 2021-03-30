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
//线程有自己的栈空间 2个cnt互相不会被影响

//全局变量，临界资源，采用互斥访问
int gNumber = 1000;//这个是个全局变量 各个子线程都可以拿到 但此时如果直接用的话  会出现乱序的 它相当于临界资源
pthread_mutex_t mutex1;
void * threadFunc1(void * args)
{
	int cnt = 1000;
	while(cnt--) {
		pthread_mutex_lock(&mutex1);
		--gNumber;
		printf("sub thread %ld, gNumber = %d\n",(uint64_t)pthread_self(),gNumber);
		pthread_mutex_unlock(&mutex1);
		sleep(1);
	}
	return NULL;
}

void * threadFunc2(void * args)
{
	int cnt = 1000;
	while(cnt--) {
		pthread_mutex_lock(&mutex1);
		--gNumber;
		printf("sub thread %ld, gNumber = %d\n",(uint64_t)pthread_self(),gNumber);
		pthread_mutex_unlock(&mutex1);
		sleep(1);
	}
	return NULL;
}
int main(void)
{
	pthread_mutex_init(&mutex1,NULL);//初始化
	printf(">> main thread starts\n");
	pthread_t pthid1 = 0,pthid2 = 0;
	// 在linux里面 线程的本质其实还是一个进程 用结构体来表示进程struct tast_struct{...}
	pthread_create(&pthid1,NULL,threadFunc1,NULL);//创建线程 对进程进行复制 在linux当中进程和线程是一样的 因为linux进程的开销不大
	pthread_create(&pthid2,NULL,threadFunc2,NULL);//创建线程
	pthread_join(pthid1,NULL);//作用  等待线程pthid执行结束，阻塞(线程挂起，不再占用cpu)
	pthread_join(pthid2,NULL);
	//while(1);使用死循环 还是有cpu的调度 还会占用cpu的时间片
	printf(">> main thread exit\n");
	return 0;
}
