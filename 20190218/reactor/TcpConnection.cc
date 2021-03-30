 ///
 /// @file    TcpConnection.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 16:42:16
 ///
 
#include "TcpConnection.h"
#include <sys/socket.h>
namespace wd
{
TcpConnection::TcpConnection(int peerfd)
: _sock(peerfd)
, _localAddr(localInetAddr())
, _peerAddr(peerInetAddr())
, _socketIO(peerfd)
, _isShutdownWrite(false)
{
	//_sock.nonblock();
}

TcpConnection::~TcpConnection()
{}

string TcpConnection::receive()
{
	char buff[65536] = {0}; // 栈开辟空间
	//::memset(buff,0,65536);
	int ret = _socketIO.readline(buff,65536);
	if(ret == 0) {//连接断开
		return string();
	} else{
		return string(buff);
	}
}

void TcpConnection::send(const string & msg)
{
	int ret = _socketIO.writen(msg.data(),msg.size());
	if(ret != msg.size()) {
		// LogInfo("send msg error");
	}
}

InetAddress TcpConnection::localInetAddr()
{
	struct sockaddr_in localaddr;
	socklen_t len = sizeof(struct sockaddr_in);
	int ret = ::getsockname(_sock.fd(),(struct sockaddr*)&localaddr,&len);
	if(ret == -1) {
		::perror(" >> getsockname");
	}
	return InetAddress(localaddr);
}

InetAddress TcpConnection::peerInetAddr()
{
	struct sockaddr_in peeraddr;
	socklen_t len = sizeof(struct sockaddr_in);
	int ret = ::getpeername(_sock.fd(),(struct sockaddr*)&peeraddr,&len);
	if(ret == -1) {
		::perror(">> getpeername");
	}
	return InetAddress(peeraddr);
}
} // end of namespace wd
