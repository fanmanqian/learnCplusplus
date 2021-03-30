 ///
 /// @file    InetAddress.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 13:18:50
 ///
 
#include "InetAddress.h"
#include<arpa/inet.h>
#include<string.h>
namespace wd
{

InetAddress::InetAddress(const string & ip,unsigned short port)
{
	::memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.data());
}

InetAddress::InetAddress(unsigned short port)
{
	::memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;//代表本机地址
}
string InetAddress::ip() const
{
	return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const
{
	return ntohs(_addr.sin_port);	
}

}// end of namespace wd
