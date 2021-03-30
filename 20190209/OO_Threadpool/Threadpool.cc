 ///
 /// @file    Threadpool.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 21:23:59
 ///
 
#include "Threadpool.h"
#include "WorkerThread.h"
#include <unistd.h>
 
namespace wd
{

Threadpool::Threadpool(size_t threadNum,size_t taskNum)
: _threadNum(threadNum)
, _threads()
, _taskNum(taskNum)
, _taskque(_taskNum)
, _isExit(false)
{
	_threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
	if(!_isExit) {
		stop();
	}
}

void Threadpool::start()
{
	for(size_t idx = 0; idx < _threadNum; ++idx) {
		unique_ptr<Thread> up(new WorkerThread(*this));
		_threads.push_back(std::move(up));
	}
	for(auto & threadPtr : _threads) {
		threadPtr->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit) {
		//在退出线程池之前，要确保所有的任务都被执行完毕了
		while(!_taskque.empty()) {
			::sleep(1);
		}
		//退出while循环.表示所有的任务都被子线程取走了
		_isExit = true;
		//回收每一个子线程的资源
		for(auto & threadPtr : _threads) {
			threadPtr->join();//等待每一个子线程执行完毕
		}
	}
}

void Threadpool::threadFunc()
{
	while(!_isExit) {
		TaskType ptask = getTask();
		if(ptask) {
			ptask->process();
		}
	}
}

TaskType Threadpool::getTask()
{
	return _taskque.pop();	
}

void Threadpool::addTask(TaskType task)
{	
	return _taskque.push(task);
}

}// end of namespace wd
