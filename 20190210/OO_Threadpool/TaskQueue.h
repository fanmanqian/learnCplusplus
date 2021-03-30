 ///
 /// @file    TaskQueue.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 14:09:02
 ///
 
#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H_

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;
namespace wd
{
class Task;
using TaskType = Task*;
class TaskQueue
{
public:
	TaskQueue(size_t size)
	: _queSize(size)
	, _taskque()
	, _mutex()
	, _notFull(_mutex)
	, _notEmpty(_mutex)
	, _used(true)
	{}

	bool empty() const;
	bool full() const;

	void push(const TaskType &);
	void wakeup();//唤醒所有其他线程
	TaskType pop();
private:
	size_t _queSize;
	queue<TaskType> _taskque;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _used;//判断是否使用队列
};
}//end of wd_

#endif
