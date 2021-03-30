 ///
 /// @file    Acceptor.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 13:45:12
 ///
 
#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H_

#include "Socket.h"
#include "InetAddress.h"
namespace wd
{

class Acceptor
{
public:
	Acceptor(const string & ip,unsigned short port);
	Acceptor(unsigned short port);
	
	void ready();
	int accept();
	int fd() const;
private:
	void setReuseAddr();
	void setReusePort();
	void bind();
	void listen();
private:
	Socket _sock;
	InetAddress _addr;
};
}// end of namespace wd

#endif
