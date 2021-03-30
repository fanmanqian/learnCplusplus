 ///
 /// @file    TcpConnection.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 16:30:46
 ///
 
#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"

#include <string>
using std::string;

namespace wd
{
class TcpConnection
{
public:
	explicit
	TcpConnection(int peerfd);
	~TcpConnection();

	string receive();
	void send(const string & msg);

private:
	InetAddress localInetAddr();
	InetAddress peerInetAddr();

private:
	Socket _sock;
	InetAddress _localAddr;
	InetAddress _peerAddr;
	SocketIO _socketIO;
	bool _isShutdownWrite;
};
}//end of namespace wd

#endif
