 ///
 /// @file    EventLoop.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-10 18:53:37
 ///
 
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _acceptor(acceptor)
, _eventsList(1024)
, _isLooping(false)
{
	addEpollReadFd(_acceptor.fd());
}

EventLoop::~EventLoop()
{
	::close(_efd);
}

void EventLoop::loop()
{
	_isLooping = true;
	while(_isLooping) {
		waitEpollFds();
	}
}

void EventLoop::unloop()
{
	if(_isLooping) {
		_isLooping = false;
	}
}

void EventLoop::waitEpollFds()
{
	int nready;
	do{
		nready = ::epoll_wait(_efd,&*_eventsList.begin(),_eventsList.size(),5000);
	}while(nready == -1 && errno == EINTR);
	if(nready == 0) {
		printf(">> epoll_wait time out.\n");
	} else if(nready == -1) {
		::perror(">> epoll_wait");
		return;
	} else {
		if(nready == _eventsList.size()) {
			_eventsList.resize(2 * _eventsList.size());
		}
		for(int idx = 0; idx < nready; ++idx) {
			if(_eventsList[idx].data.fd == _acceptor.fd() &&
					_eventsList[idx].events & EPOLLIN) {
				handleNewConnection();
			} else {
				handleMessage(_eventsList[idx].data.fd);
			}
		}
	}
}

void EventLoop::handleNewConnection()
{
	int peerfd = _acceptor.accept();
	addEpollReadFd(peerfd);

	shared_ptr<TcpConnection> conn(new TcpConnection(peerfd));
	cout << ">> " << conn->toString() << " has connected! " << endl;
	
	_conns.insert(std::make_pair(peerfd,conn));
}

void EventLoop::handleMessage(int fd) 
{
	auto iter = _conns.find(fd);
	if(iter != _conns.end()) {
		//先判断链接是否断开 
		bool closed = iter->second->isClosed();
		if(!closed) {//收到数据情况
			string msg = iter->second->receive();
		
			cout << " >> server receive: " << msg << endl;

			iter->second->send(msg);
		} else {//链接断开的情况
			cout << ">> " << iter->second->toString() << " has closed! " << endl; 
			delEpollReadFd(fd);
			_conns.erase(fd);
		}
	}
}

int EventLoop::createEpollFd()
{
	int fd = ::epoll_create1(0);
	if(fd == -1) {
		::perror(">> epoll_create1");
	}
	return fd;
}

void EventLoop::addEpollReadFd(int fd)
{

	struct epoll_event value;
	value.data.fd = fd;
	value.events = EPOLLIN;
	int ret = epoll_ctl(_efd,EPOLL_CTL_ADD,fd,&value);
	if(ret == -1) {
		perror(">> epoll_ctl");
	}
}

void EventLoop::delEpollReadFd(int fd) 
{
	struct epoll_event value;
	value.data.fd = fd;
	value.events = EPOLLIN;
	int ret = epoll_ctl(_efd,EPOLL_CTL_DEL,fd,&value);
	if(ret == -1) {
		perror(">> epoll_ctl");
	}
}


}// end of namespace wd
