 ///
 /// @file    Producer.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 14:26:49
 ///
 
#ifndef __PRODUCER_H__
#define __PRODUCER_H_

#include "TaskQueue.h"
#include <stdlib.h>
#include <iostream>
using std::endl;
using std::cout;

namespace wd
{
class Producer
{
public:
	void run(TaskQueue & taskque) 
	{
		::srand(::clock());
		int cnt = 20;
		while(cnt--) {
			int number = ::rand() % 100;
			taskque.push(number);
			cout << ">>Producer " << pthread_self()
			     << " produce data " << number << endl;
		}
	}
};
}// end of wd
#endif
