 ///
 /// @file    Thread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 16:07:51
 ///
 
#include "Thread.h"

namespace wd
{
	Thread::~Thread()
	{
		if(_isRunning) {
			pthread_detach(_pthid);
			_isRunning = false;
		}	
	}
	
	void Thread::start()
	{
		pthread_create(&_pthid,NULL,threadFunc,this);
		_isRunning = true;
	}

	void Thread::join()
	{
		if(_isRunning == true) {
			pthread_join(_pthid,NULL);
			_isRunning = false;
		}
	}

	void * Thread::threadFunc(void * arg)
	{
		Thread * p = static_cast<Thread*>(arg);
		if(p) {
			p->_threadCallback();
		}
		return NULL;
	}
}
