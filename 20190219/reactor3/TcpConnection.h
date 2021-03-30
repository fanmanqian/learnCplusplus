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
#include "Noncopyable.h"
#include <functional>
#include <memory>
#include <string>
using std::string;
using std::function;
using std::shared_ptr;

namespace wd
{
//不能对链接进行复制 所以要加上Noncopyable.h
class EventLoop;
class TcpConnection
: public Noncopyable,
public std::enable_shared_from_this<TcpConnection>
{
public:
	using TcpConnectionCallback = std::function<void(const shared_ptr<TcpConnection> &)>;

	explicit
	TcpConnection(int peerfd,EventLoop & loop);
	~TcpConnection();
	
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

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

	bool isClosed();
	string receive();
	void shutdown();
	void send(const string & msg);
	void sendInLoop(const string & msg);
	string toString() const;
private:
	InetAddress localInetAddr();
	InetAddress peerInetAddr();

private:
	Socket _sock;
	InetAddress _localAddr;
	InetAddress _peerAddr;
	SocketIO _socketIO;
	bool _isShutdownWrite;
	TcpConnectionCallback  _onConnectionCallback;
	TcpConnectionCallback  _onMessageCallback;
	TcpConnectionCallback  _onCloseCallback;
	EventLoop & _loop;
};
}//end of namespace wd

#endif
