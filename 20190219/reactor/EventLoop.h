 ///
 /// @file    EventLoop.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-10 18:45:44
 ///
 
#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <vector>
#include <map>
#include <memory>
using std::vector;
using std::map;
using std::shared_ptr;

namespace wd
{

class Acceptor;
class TcpConnection;
class EventLoop
{
public:
	EventLoop(Acceptor & acceptor);
	
	~EventLoop();
	void loop();
	void unloop();

private:
	void addEpollReadFd(int fd);
	void delEpollReadFd(int fd);
	int createEpollFd();
	void waitEpollFds();
	void handleNewConnection();
	void handleMessage(int peerfd);

private:
	int _efd;
	Acceptor & _acceptor;
	map<int,shared_ptr<TcpConnection>> _conns;
	vector<struct epoll_event> _eventsList;
	bool _isLooping;
};
}// end of namespace wd
#endif
