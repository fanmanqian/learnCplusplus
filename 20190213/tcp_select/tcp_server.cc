 ///
 /// @file    tcp_server.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-09 16:14:47
 ///

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define ERROR_EXIT(msg) do{\
	::perror(msg);\
	::exit(EXIT_FAILURE);\
}while(0)

int create_tcp_socket()
{
	int listenfd = ::socket(AF_INET,SOCK_STREAM,0);//TCP协议
	if(listenfd == -1) {
		ERROR_EXIT("socket");
	}
	return listenfd;	
}

int bind_inet_addr(int fd,const char * ip,unsigned short port)
{
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	int ret = ::bind(fd,(const struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret == -1) {
		::close(fd);
		ERROR_EXIT("socket");
	}	
	return ret;
}

int mylisten(int fd)
{
	int ret = ::listen(fd,10);
	if(ret == -1) {
		::close(fd);
		ERROR_EXIT("listen");
	}
	return ret;
}

int my_accept(int fd)
{
		int peerfd = ::accept(fd,NULL,NULL);
		if(peerfd == -1) {
			::close(fd);
			perror("accept");
		}
		return peerfd;
}

int handle_new_connection(int listenfd)
{	
		int peerfd = my_accept(listenfd);
		cout << " >> server serve client with fd = " << peerfd << endl;
		struct sockaddr_in clientaddr;//4.1 解析对端Ip和Port
		::memset(&clientaddr, 0, sizeof(struct sockaddr_in));
		socklen_t len = sizeof(struct sockaddr_in);
		int ret = ::getpeername(peerfd, (struct sockaddr *)(&clientaddr), &len);
		
		struct sockaddr_in serveraddr;
		::memset(&serveraddr, 0, sizeof(struct sockaddr_in));
		int ret1 = ::getsockname(peerfd, (struct sockaddr *)(&serveraddr), &len);

		if(ret1 == -1) {
			perror("getsockname");
		} else {
			cout << " clientaddr len = " << len << endl;
			string serverip(inet_ntoa(serveraddr.sin_addr));//二进制的地址转换为点分十进制的ip地址
			unsigned short serverport = ntohs(serveraddr.sin_port);//大端模式转换为小端模式
			cout << " >>> server " << serverip << ":" << serverport;
		}

		if(ret == -1) {
			perror("getpeername");
		} else {
			cout << " clientaddr len = " << len << endl;
			string clientip(inet_ntoa(clientaddr.sin_addr));//二进制的地址转换为点分十进制的ip地址
			unsigned short clientport = ntohs(clientaddr.sin_port);//大端模式转换为小端模式
			cout << " --> " << " client " << clientip << ":" << clientport
				 << " has connected!" << endl;
		}
		return peerfd;
}

void receive_data(int peerfd,fd_set * rfds)
{
		//5. 对已经建立好的链接进行数据的接收
		char buff[1024] = {0}; //应用层接收缓冲区
		cout << "before recv" << endl;

		int ret = ::recv(peerfd, buff, sizeof(buff), 0);//默认情况下是一个阻塞式函数
		cout << " >> server recv ret = " << ret << endl;
		if(ret < 0) {
			if(ret == -1 && errno == EINTR)
				return ;
			else 
				perror("recv");
		} else if(ret == 0) { //连接已经断开了
			::close(peerfd);
			FD_CLR(peerfd,&rfds);
		} else {
		//ret表示已经接收到了的对端数据的长度
		//6. 对接收的数据进行处理（业务逻辑）
		//....
		cout << " >> server gets msg from client : " << buff << endl;
		//7. 进行数据的发送，回显操作
		ret = ::send(peerfd,buff,strlen(buff),0);
		if(ret == -1) {
			::close(peerfd);
			FD_CLR(peerfd, &rfds);
			perror("send");
		}
		//8. 断开连接
		::close(peerfd); //关闭连接,回收文件描述符 
		FD_CLR(peerfd, &rfds);
		}
}

void set_reuse_addr(int fd,int on)
{
	socklen_t reuse = on;
	::setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(const void *)&reuse,sizeof(socklen_t))
}

void test0() 
{
	int listenfd = create_tcp_socket();
	cout << " >>>> server listenfd = " << listenfd << endl;
	string ip("192.168.146.144");
	unsigned short port = 8888;
	bind_inet_addr(listenfd, ip.data(), port);
	mylisten(listenfd);
	//并发服务器模型之IO复用select
	fd_set rfds;//读事件的fd_set
	FD_ZERO(&rfds);
	FD_SET(listenfd,&rfds);//将listenfd添加到select监听队列中
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	while(true) {
		//4. 建立新连接
		cout << " >> server is about to accept new link " << endl;
		int ready = ::select(1024,&rfds,nullptr,nullptr,&tv);
		if(ready == -1 && errno == EINTR) {
			continue;
		} else if(ready == -1) {	
			perror("select");
		} else if(ready) {
			for(int fd = 0; fd < 1024; ++fd) {
				if(FD_ISSET(fd,&rfds) && fd == listenfd) {
					int peerfd = handle_new_connection(fd);
					FD_SET(peerfd, &rfds);
				}
				if(FD_ISSET(fd,&rfds) && fd != listenfd) {
					receive_data(fd,&rfds);
				}
			}
		} else {
			cout << " time out: No data within five seconds. " << endl;
		}
	} 
	::close(listenfd);//文件描述符资源是有限的
	FD_CLR(listenfd, &rfds);
}

int main(void)
{
	test0();
	return 0; 
}
