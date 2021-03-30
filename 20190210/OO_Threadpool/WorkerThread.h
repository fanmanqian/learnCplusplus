 ///
 /// @file    MyThread.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 21:48:03
 ///
 
#ifndef __WD_MYTHREAD_H__
#define __WD_MYTHREAD_H_
#include "Thread.h"

namespace wd
{
class Threadpool;

class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool);
private:
	void run() override;
private:
	Threadpool & _threadpool;
};
}// end of namespace wd
#endif
