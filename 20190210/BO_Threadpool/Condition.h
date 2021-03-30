 ///
 /// @file    Condition.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-03 13:37:01
 ///
 
#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{

class MutexLock;
class Condition
: Noncopyable
{
public:
	Condition(MutexLock &);
	~Condition();

	void wait();
	void notify();
	void notifyall();
private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};
}//end of namespace 
#endif
