 ///
 /// @file    EventLoop.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-10 18:53:37
 ///
 
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <sys/eventfd.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _eventfd(createEventFd())
, _acceptor(acceptor)
, _eventsList(1024)
, _isLooping(false)
{
	addEpollReadFd(_acceptor.fd());
	addEpollReadFd(_eventfd);
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

void EventLoop::runInLoop(Functor && cb)
{
	//成为临界资源
	{
		MutexLockGuard autolock(_mutex);
		_pendingFunctors.push_back(std::move(cb));
	}
	wakeup();//通知IO线程执行发送操作
}

void EventLoop::doPendingFunctors()
{
	//由于是临界资源所以不能这样直接执行
	//我们先用个临时的tmp替换原来functors里面的内容
	vector<Functor> tmp;
	{
		MutexLockGuard autolock(_mutex);
		tmp.swap(_pendingFunctors);
	}

	for(auto & functor : tmp) {
		functor();
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
			} else if(_eventsList[idx].data.fd == _eventfd) {
				handleRead();
				doPendingFunctors();
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

	shared_ptr<TcpConnection> conn(new TcpConnection(peerfd,*this));
	_conns.insert(std::make_pair(peerfd,conn));
//	cout << ">> " << conn->toString() << " has connected! " << endl;
	// do something (写死了) 如果想做定制化操作，就必须修改源码	
	//cout << ">> " << conn->toString() << " has connected! " << endl;
	conn->setConnectionCallback(_onConnectionCallback);
	conn->setMessageCallback(_onMessageCallback);
	conn->setCloseCallback(_onCloseCallback);

	conn->handleConnectionCallback();//相当于挖空再填上
}

void EventLoop::handleMessage(int fd) 
{
	auto iter = _conns.find(fd);
	if(iter != _conns.end()) {
		//先判断链接是否断开 
		bool closed = iter->second->isClosed();
		if(!closed) {//收到数据情况
			iter->second->handleMessageCallback();
		} else {//链接断开的情况
			//do something
			iter->second->handleCloseCallback();
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

int EventLoop::createEventFd()
{
	int fd = ::eventfd(0,0);
	if(fd == -1) {
		::perror(">> eventfd_create");
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

void EventLoop::handleRead()
{
	uint64_t howmany = 0;
	int ret = ::read(_eventfd,&howmany,sizeof(howmany));
	if(ret!=sizeof(howmany)) {
		::perror(">> read");
	}
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	int ret = ::write(_eventfd,&one,sizeof(one));
	if(ret!=-1) {
		::perror(">> write");
	}
}

}// end of namespace wd
