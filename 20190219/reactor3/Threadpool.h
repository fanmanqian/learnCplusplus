 ///
 /// @file    Threadpool.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 21:18:03
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <memory>
#include <functional>
using std::vector;
using std::unique_ptr;
using std::function;

namespace wd
{
using TaskType = function<void()>;
class Thread;
class Threadpool
{
public:
	Threadpool(size_t,size_t);
	~Threadpool();
	void start();//开启线程池
	void stop();//关闭线程池
private:
	void threadFunc();//每一个线程要执行的任务
	TaskType getTask();
public:
	void addTask(TaskType &&);
private:
	size_t _threadNum;
	vector<unique_ptr<Thread>> _threads;
	size_t _taskNum;
	TaskQueue _taskque;
	bool _isExit;
};
}// end of namespace wd
#endif
