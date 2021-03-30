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
#include <unordered_set>
using std::cout;
using std::endl;
using std::string;
using std::unordered_set;

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

void set_reuse_addr(int fd,int on)
{
	socklen_t reuse = on;
	if(::setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(const void *)&reuse,sizeof(socklen_t))) {
		ERROR_EXIT("setsockopt");
	}
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

void handle_client_message(int peerfd,fd_set * rfds,unordered_set<int> & client_fds)
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
			FD_CLR(peerfd,rfds);
			client_fds.erase(peerfd);
		} else {
		//ret表示已经接收到了的对端数据的长度
		//6. 对接收的数据进行处理（业务逻辑）
		//....
		//do something....
		//
		cout << " >> server gets msg from client : " << buff << endl;
		//7. 得到要返回给client的结果，对数据进行发送(回显操作能够正常进行，表示服务器框架搭建完毕)
		ret = ::send(peerfd,buff,strlen(buff),0);//传输层操作对于我们来说是透明的
		if(ret == -1) {
			::close(peerfd);
			FD_CLR(peerfd, rfds);
			perror("send");
		}
		//8. 断开连接
		::close(peerfd); //关闭连接,回收文件描述符 
		FD_CLR(peerfd, rfds);
		client_fds.erase(peerfd);
		}
}

int tcp_server(const string & ip,unsigned short port)
{
	int listenfd = create_tcp_socket();
	cout << " >>>> server listenfd = " << listenfd << endl;
	bind_inet_addr(listenfd, ip.data(), port);
	set_reuse_addr(listenfd,1);//将网络地址设置成可以重用的
	mylisten(listenfd);
	return listenfd;	
}

void set_non_block(int peerfd)
{
	int flags = ::fcntl(peerfd,F_GETFL,0);
	if(flags == -1) {
		ERROR_EXIT("fcntl");
	}
	int ret = ::fcntl(peerfd,F_SETFL,O_NONBLOCK | flags);
	if(ret == -1) {
		ERROR_EXIT("fcntl");
	}
}

void select_fds_init(int & maxval,fd_set * rfds,unordered_set<int> & client_fds)
{
	for(auto & fd : client_fds) {
		FD_SET(fd,rfds);
		if(maxval < fd) maxval = fd;
	}
}

void test0() 
{
	string ip("192.168.146.144");
	unsigned short port = 8888;
	int listenfd = tcp_server(ip,port);
	//并发服务器模型之IO复用select
	fd_set rfds;//读事件的fd_set
//	struct timeval tv;
//	tv.tv_sec = 5;
//	tv.tv_usec = 0;
	int maxfd = 1024;
	unordered_set<int> client_fds;//存储的是已经建立连接的fd 
	while(true) {
		//每次调用select前都要重新设置fd和时间
		//因为事件发生后，fd和时间都被内核修改了
		FD_ZERO(&rfds);
		FD_SET(listenfd, &rfds);//将listenfd添加到select监听队列中
		select_fds_init(maxfd, &rfds, client_fds);
		int ready = ::select(maxfd,&rfds,nullptr,nullptr,nullptr);//阻塞式函数
		cout << " >>> select retval = " << ready << endl;
		if(ready == -1 && errno == EINTR) {
			continue;
		} else if(ready == -1) {	
			ERROR_EXIT("select");
		} else if(ready) {
			//ready > 0 
			for(int fd = 0; fd < maxfd; ++fd) {
				if(FD_ISSET(fd,&rfds) && fd == listenfd) {
					//处理新连接
					int peerfd = handle_new_connection(fd);
					set_non_block(peerfd);//设置成非阻塞的
					FD_SET(peerfd,&rfds);
					client_fds.insert(peerfd);
				}
				if(FD_ISSET(fd,&rfds) && fd != listenfd) {
					//处理已经建立好的链接
					handle_client_message(fd,&rfds,client_fds);
				}
			}
		} else {
			cout << " time out." << endl;
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
