 ///
 /// @file    WorkerThread.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 22:21:18
 ///
 
#include "WorkerThread.h"
#include "Threadpool.h"

namespace wd
{

WorkerThread::WorkerThread(Threadpool & threadpool)
: _threadpool(threadpool)
{
		
}

void WorkerThread::run()
{
	_threadpool.threadFunc();
}
}// end of namespace wd
