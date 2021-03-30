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
#include <functional>
using std::cout;
using std::endl;


namespace wd
{
class Thread
: Noncopyable
{
public:
	//typedef ThreadCallback function<void()>;
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && threadCallback)
	: _threadCallback(std::move(threadCallback))
	, _pthid(0)
	, _isRunning(false)
	{}

	~Thread();
	void start();
	void join();
private:
	static void * threadFunc(void * arg);
private:
	ThreadCallback _threadCallback;
	pthread_t _pthid;
	bool _isRunning;
};
}//end of namespace
#endif
