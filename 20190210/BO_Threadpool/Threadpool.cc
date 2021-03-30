 ///
 /// @file    Threadpool.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 21:23:59
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <algorithm>
 
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
		unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFunc,this)));
		_threads.push_back(std::move(up));
	}
	for(auto & threadPtr : _threads) {
		threadPtr->start();
	}
}
//停止线程池
void Threadpool::stop()
{
	cout << " >>> main thread threadpool::stop() entering" << endl;
	if(!_isExit) {
		//在退出线程池之前，要确保所有的任务都被执行完毕了
		while(!_taskque.empty()) {
			//::sleep(1);//bug:如果在休眠的过程中，所有的子线程已经将任务执行完毕，并且阻塞在getTask方法之上
					   //即使将_isExit设置为true，子线程也不会正常退出
			::usleep(100); // 为了防止CPU空转 ，让线程休眠100微妙
		}
		//退出while循环.表示所有的任务都被子线程取走了(任务是否执行完毕不确定)
		_isExit = true;
		//我们阻塞的原因是存在没有抢到最后一个任务的线程  那么这些线程就会阻塞导致无法正常退出
		//所以我们要做的就是唤醒这些被阻塞的线程就可以了
		_taskque.wakeup();
		//回收每一个子线程的资源
		for(auto & threadPtr : _threads) {
			threadPtr->join();//等待每一个子线程执行完毕
		}
	}
	cout << " >>> main thread threadpool::stop() exit" << endl; 
}

void Threadpool::threadFunc()
{
	while(!_isExit) {
		TaskType ptask = getTask();
		if(ptask) {
			ptask();
		}
	}
}

TaskType Threadpool::getTask()
{
	return _taskque.pop();	
}

void Threadpool::addTask(TaskType && task)
{	
	return _taskque.push(std::move(task));
}

}// end of namespace wd
