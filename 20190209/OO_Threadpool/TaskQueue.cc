 ///
 /// @file    TaskQueue.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 14:15:11
 ///
 
#include "TaskQueue.h"
#include <iostream>
using std::cout;
using std::endl;


namespace wd
{

bool TaskQueue::empty() const
{
	return _taskque.empty();
}

bool TaskQueue::full() const
{
	return _taskque.size() == _queSize; 
}
//pop方法运行在消费者线程
TaskType TaskQueue::pop()
{
	MutexLockGuard autolock(_mutex);
	while(empty()) {
		_notEmpty.wait();
//		cout << "queue is empty! can not pop!" << endl;
	}
	TaskType number = _taskque.front();
	_taskque.pop();
	_notFull.notify();//通知生产者线程放数据
	return number;
}
//push方法运行在生产者线程
void TaskQueue::push(const TaskType & number)
{
	MutexLockGuard autolock(_mutex);
	while(full()) {
//		cout << "queue is full! can not push!" << endl;
		_notFull.wait();//使用while可以防止_notFull被异常唤醒
	}
	_taskque.push(number);//生产者线程放数据
	_notEmpty.notify();//通知消费者线程取数据
}

}//end of wd
