 ///
 /// @file    Socket.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 13:27:49
 ///
 
#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

namespace wd
{

class Socket
{

public:
	Socket();
	explicit Socket(int);

	~Socket();
	
	int fd() const;
	void nonblock();

	void shutdownWrite();

private:
	int _fd;
};
}// end of namespace 
#endif
