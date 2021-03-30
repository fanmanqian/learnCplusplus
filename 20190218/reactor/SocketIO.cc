 ///
 /// @file    SocketIO.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 18:13:34
 ///
 
#include "SocketIO.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include<sys/types.h>
#include<sys/socket.h>
namespace wd
{

int SocketIO::readn(char * buff,int len)
{
	char * p = buff;
	int left = len;
	while(left > 0) {
		int ret = ::read(_fd,p,left);
		if(ret==-1&&errno == EINTR) {
			continue;
		} else if(ret==-1) {
			perror(">> read");
			return len - left;
		} else if(ret == 0) {
			return len - left;
		} else if(ret > 0){
			left -= ret;
			p += ret;
		}
	}
	return len - left;
}

int SocketIO::writen(const char * buff,int len)
{
	const char * p = buff;
	int left = len;
	while(left > 0) {
		int ret = ::write(_fd,p,left);
		if(ret==-1&&errno == EINTR) {
			continue;
		} else if(ret==-1) {
			perror(">> writen");
			return len - left;
		} else {
			left -= ret;
			p += ret;
		}
	}
	return len - left;
}

int SocketIO::recvPeek(char * buff,int len)
{
	int ret = 0;
	do{
	  ret = ::recv(_fd,buff,len,MSG_PEEK);//并未移走内核缓冲区的数据
	}while(ret == -1 && errno == EINTR);
	return ret;
}

int SocketIO::readline(char * buff,int maxlen)
{
	int left = maxlen - 1;
	char * p = buff;
	int  total = 0;//已经从内核缓冲区中移走的数据
	while(left > 0) {
		int ret = recvPeek(p,left);//没有移走
		for(int idx = 0; idx < ret; ++idx) {
			if(p[idx] == '\n') {
				int size = idx + 1;
				readn(p, idx + 1);//从内核缓冲区中移走数据
				total += size;
				p += size;
				*p = '\0';
				return total;
			}
		}
		readn(p,ret);
		p += ret;
		left -= ret;
		total += ret;
	}
	*p = '\0';
	return total;
}
}// end of namespace 
