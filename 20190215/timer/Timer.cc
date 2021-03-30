 ///
 /// @file    Timer.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-20 15:52:10
 ///
 
#include "Timer.h"
#include <sys/timerfd.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <poll.h>
#include <iostream>
using std::cout;
using std::endl;
 
namespace wd
{

Timer::Timer(TimerCallback && callback,int initialTime,int periodicTime)
: _fd(createTimerfd())
, _initialTime(initialTime)
, _periodicTime(periodicTime)
, _callback(std::move(callback))
, _isStarted(false)
{

}

Timer::~Timer()
{
	if(_isStarted) {
		stop();
	}
}

int Timer::createTimerfd()
{
	int fd = timerfd_create(CLOCK_REALTIME,0);
	if(fd == -1) {
		perror(" >> timerfd_create");
	}
	return fd;
}

void Timer::setTimerfd(int initialTime,int periodicTime)
{	
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = periodicTime;
	value.it_interval.tv_nsec = 0;
	int ret = ::timerfd_settime(_fd,0,&value,nullptr);
	if(ret == -1) {
		perror(">> timer_settime");
	}
}

void Timer::start()
{
	struct pollfd fds;
	fds.fd = _fd;
	fds.events = POLLIN;
	_isStarted = true;
	setTimerfd(_initialTime,_periodicTime);
	while(_isStarted) {
		int ready = ::poll(&fds,1,6000);//定时器结合poll的使用
		if(ready == -1 && errno == EINTR) {
			continue;
		} else if(ready == -1) {
			perror(">>poll");
			exit(EXIT_FAILURE);
		} else if(ready == 0) {
			cout << " poll time out." << endl;
		} else {
			if(fds.fd == _fd && (fds.revents & POLLIN))	{
				//对读事件进行处理
				handleRead();
				//执行任务
				if(_callback) {
					_callback();
				}
			}
		}
	}
}

void Timer::stop()
{
	if(_isStarted) {
		_isStarted = false;
		setTimerfd(0,0);
	}
}

void Timer::handleRead()
{
	uint64_t howmany = 0;
	int ret = ::read(_fd,&howmany,sizeof(uint64_t));
	if(ret != sizeof(howmany)) {
		perror(">>read");
	}
}
}// end of namespace 
