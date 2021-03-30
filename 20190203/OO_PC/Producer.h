 ///
 /// @file    Producer.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 14:26:49
 ///
 
#ifndef __PRODUCER_H__
#define __PRODUCER_H_

#include "TaskQueue.h"
#include "Thread.h"

namespace wd
{
class Producer
: public Thread
{
public:
	Producer(TaskQueue & taskque)
	: _taskque(taskque)
	{}

	void run() override
	{
		::srand(::clock());
		int cnt = 20;
		while(cnt--) {
			int number = ::rand() % 100;
			_taskque.push(number);
			cout << ">>Producer " << pthread_self()
			     << " produce data " << number << endl;
		}
	}

private:
	TaskQueue & _taskque;
};
}//
#endif
