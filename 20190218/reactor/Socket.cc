 ///
 /// @file    Socket.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 13:32:33
 ///
 
#include "Socket.h"

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
namespace wd
{

Socket::Socket()
{
	_fd = ::socket(AF_INET,SOCK_STREAM,0);
	if(_fd == -1){
		perror(">>> socket");
		//LogError()
	}
	//LogDebug
}

Socket::Socket(int fd)
: _fd(fd)
{

}

Socket::~Socket()
{
	::close(_fd);
}

void Socket::shutdownWrite()
{
	int ret = ::shutdown(_fd,SHUT_WR);
	if(ret!=0) {
		perror(">>> shutdown");
		//LogError
	}
}

int Socket::fd() const
{
	return _fd;
}

void Socket::nonblock()
{
	int flags = ::fcntl(_fd,F_GETFL,0);
	if(flags == -1) {
		::perror("fcntl");
	}
	int ret = ::fcntl(_fd,F_SETFL,O_NONBLOCK | flags);
	if(ret == -1) {
		perror("fcntl");
	}
}

}// end of namespace wd
