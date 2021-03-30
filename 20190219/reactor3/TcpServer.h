 ///
 /// @file    TcpServer.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-10 21:57:16
 ///
 
#ifndef __WD_TCOSERVER_H__
#define __WD_TCOSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"
#include <functional>
#include <memory>
#include <string>
using std::function;
using std::shared_ptr;
using std::string;

namespace wd
{
class TcpConnection;
class TcpServer
{
public:
	using TcpConnectionCallback = function<void(const shared_ptr<TcpConnection> )>;
	TcpServer(const string & ip, unsigned short port)
	: _acceptor(ip,port)
	, _loop(_acceptor) 
	{}
	
	void start()
	{
		_acceptor.ready();
		_loop.loop();
	}

	void setConnectionCallback(TcpConnectionCallback && cb)
	{
		_loop.setConnectionCallback(std::move(cb));
	}	

	void setCloseCallback(TcpConnectionCallback && cb)
	{
		_loop.setCloseCallback(std::move(cb));
	}

	void setMessageCallback(TcpConnectionCallback && cb)
	{
		_loop.setMessageCallback(std::move(cb));
	}

private:
	Acceptor _acceptor;
	EventLoop _loop;
};
}// end of namespace wd



#endif
