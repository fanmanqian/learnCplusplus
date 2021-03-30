 ///
 /// @file    Consumer.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 14:42:14
 ///
 
#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include <iostream>
using std::cout;
using std::endl;
 
namespace wd
{
class Consumer
{
public:
	void run(TaskQueue & taskqueue) 
	{
		int cnt = 20;
		while(cnt--) {
			int number = taskqueue.pop();
			cout << ">>Consumer " << pthread_self() << " produces a number "
				 << number << endl;
		}
	}
};
}// end of wd
#endif
