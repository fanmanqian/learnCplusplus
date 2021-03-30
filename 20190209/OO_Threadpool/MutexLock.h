 ///
 /// @file    MutexLock.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-03 13:48:45
 ///
 
#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{

class MutexLock
: Noncopyable
{
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();
	pthread_mutex_t * getPtr(){ return &_mutex;}
private:
	pthread_mutex_t _mutex;
};
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}
private:
	MutexLock & _mutex;
};
}//end of wd
#endif
