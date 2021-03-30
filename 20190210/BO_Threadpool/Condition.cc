 ///
 /// @file    Condition.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-03 13:40:50
 ///
 
#include "Condition.h"
#include "MutexLock.h"
#include <stdio.h>
#include <errno.h>
#include <iostream>
using std::cout;
using std::endl;
 
namespace wd
{
	Condition::Condition(MutexLock & mutex)
	: _mutex(mutex)
	{
		if(pthread_cond_init(&_cond,NULL)) {
			perror("pthread_cond_init");
		}
	}

	Condition::~Condition()
	{
		if(pthread_cond_destroy(&_cond)) {
			perror("pthread_cond_destroy");
		}
	}

	void Condition::wait()
	{
		if(pthread_cond_wait(&_cond,_mutex.getPtr())) {
			perror("pthread_cond_destroy");
		}
	}

	void Condition::notify()
	{
		if(pthread_cond_signal(&_cond)) {
			perror("pthread_cond_signal");
		}
	}

	void Condition::notifyall() 
	{
		if(pthread_cond_broadcast(&_cond)) {
			perror("pthread_cond_broadcast");
		}
	}


}//end of wd
