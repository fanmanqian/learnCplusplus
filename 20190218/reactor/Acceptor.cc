 ///
 /// @file    Acceptor.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 15:48:21
 ///
 
#include "Acceptor.h"

namespace wd
{

Acceptor::Acceptor(const string & ip,unsigned short port)
: _sock()
, _addr(ip,port)
{}

Acceptor::Acceptor(unsigned short port)
: _sock()
, _addr(port)
{}

void Acceptor::ready()
{
	setReuseAddr();
	setReusePort();
	bind();
	listen();
}

int Acceptor::fd() const
{
	return _sock.fd();
}

void Acceptor::setReuseAddr()
{
	int reuse = 1;
	if(::setsockopt(fd(),SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int))) {
		::perror(">>> setreuseAddr");		
	}
}

void Acceptor::setReusePort()
{
	int reuse = 1;
	if(::setsockopt(fd(),SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(int))) {
		::perror(">>> setreusePort");		
	}
}

void Acceptor::bind()
{
	int ret = ::bind(fd(),(const struct sockaddr *)_addr.getSockaddrPtr(),sizeof(InetAddress));
	if(ret == -1) {
		perror(">> bind");
	}
}

void Acceptor::listen()
{
	int ret = ::listen(fd(),10);
	if(-1 == ret) {
		::perror("listen");
	}
}

int Acceptor::accept()
{
	int peerfd = ::accept(fd(),nullptr,nullptr);
	if(peerfd == -1) {
		perror(">>accept");
	}
	return peerfd;
}

} // end of namespace wd
