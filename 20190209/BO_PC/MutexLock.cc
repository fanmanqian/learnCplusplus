 ///
 /// @file    MutexLock.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-03 13:50:49
 ///
 
#include "MutexLock.h"

#include <iostream>
using std::cout;
using std::endl;
 
namespace wd
{

	MutexLock::MutexLock()
	{
		pthread_mutex_init(&_mutex,NULL);
	}
	
	MutexLock::~MutexLock()
	{
		pthread_mutex_destroy(&_mutex);
	}

	void MutexLock::lock()
	{
		pthread_mutex_lock(&_mutex);
	}

	void MutexLock::unlock()
	{
		pthread_mutex_unlock(&_mutex);
	}


}//end of wd
