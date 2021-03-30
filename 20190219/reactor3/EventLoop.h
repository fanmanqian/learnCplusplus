 ///
 /// @file    EventLoop.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-10 18:45:44
 ///
 
#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__
#include "MutexLock.h"
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <vector>
#include <map>
#include <functional>
#include <memory>
using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

namespace wd
{

class Acceptor;
class TcpConnection;
class EventLoop
{
public:
	using Functor = std::function<void()>;
	using TcpConnectionCallback = function<void(const shared_ptr<TcpConnection>)>;
	EventLoop(Acceptor & acceptor);
	
	~EventLoop();
	void loop();
	void unloop();
	
	void doPendingFunctors();
	void setConnectionCallback(TcpConnectionCallback && cb)
	{
		_onConnectionCallback = std::move(cb);
	}

	void setMessageCallback(TcpConnectionCallback && cb) 
	{
		_onMessageCallback = std::move(cb);
	}

	void setCloseCallback(TcpConnectionCallback && cb)
	{
		_onCloseCallback = std::move(cb);
	}

	void runInLoop(Functor && cb);
private:
	void addEpollReadFd(int fd);
	void delEpollReadFd(int fd);
	int createEpollFd();
	int createEventFd();
	void waitEpollFds();
	void handleNewConnection();
	void handleMessage(int peerfd);
	void handleRead();
	void wakeup();

private:
	int _efd;
	int _eventfd;
	Acceptor & _acceptor;
	map<int,shared_ptr<TcpConnection>> _conns;
	vector<struct epoll_event> _eventsList;
	bool _isLooping;

	MutexLock _mutex;
	vector<Functor> _pendingFunctors;
	TcpConnectionCallback  _onConnectionCallback;
	TcpConnectionCallback  _onMessageCallback;
	TcpConnectionCallback  _onCloseCallback;
	
};
}// end of namespace wd
#endif
