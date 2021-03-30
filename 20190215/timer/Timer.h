 ///
 /// @file    Timer.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-20 15:28:04
 ///
 
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__

#include <functional>

namespace wd
{
class Timer
{
public:
	using TimerCallback = std::function<void()>;
	Timer(TimerCallback &&,int,int);
	~Timer();
	void start();
	void stop();
private:
	int createTimerfd();
	void setTimerfd(int,int);
	void handleRead();
private:
	int _fd;
	int _initialTime;
	int _periodicTime;
	TimerCallback _callback;
	bool _isStarted;
};
} //  end of namespace 

#endif
