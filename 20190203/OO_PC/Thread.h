 ///
 /// @file    Thread.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:03:14
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include <pthread.h>
#include "Noncopyable.h"
#include <iostream>
using std::cout;
using std::endl;


namespace wd
{
class Thread
: Noncopyable
{
public:
	Thread()
	: _pthid(0)
	, _isRunning(false)
	{}


	virtual 
	~Thread();

	void start();
	void join();
private:
	virtual
	void run() = 0;//这是想线程要执行的任务
	static void * threadFunc(void * arg);
private:
	pthread_t _pthid;
	bool _isRunning;
};
}//end of namespace
#endif
