 ///
 /// @file    tcp_client.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-13 22:18:29
 ///
 
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;

#define ERROR_EXIT(msg) do{\
	perror(msg);\
	exit(EXIT_FAILURE);\
}while(0)

void client_test()
{
	//1. 创建客户端套接字
	int clientfd = ::socket(AF_INET, SOCK_STREAM,0);
	if(clientfd == -1) {
		ERROR_EXIT("socket");
		return ;
	}
	
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8888);//::这里不能用 用了会报错
	serveraddr.sin_addr.s_addr = inet_addr("192.168.146.144");

	//2. 客户端发起连接请求
	cout << " >> client is about to connect server..." << endl;
	int ret = ::connect(
			clientfd, 
		    (const struct sockaddr*)&serveraddr, 
			sizeof(serveraddr));
	if(ret == -1) {
		ERROR_EXIT("connect");
		close(clientfd);
	}
	
	//3. 连接建立好之后，发送数据
	cout << " >> connect success..." << endl;
	cout << " >>pls input data:";
	while(true) {
		string data;//要发送的数据
		cin >> data;//cin往data里面去写数据
	
		//只是把数据从应用层缓冲区复制到了内核缓冲区，数据的发送靠内核（TCP协议栈）完成的 
		ret = ::send(clientfd,data.c_str(),data.size(),0);
		if(ret == -1) {
			ERROR_EXIT("send");
			close(clientfd);
		}
	
		//5. 接受服务器返回的数据
		char buff[1024] = {0}; // 客户端的应用层缓冲区
		//只是把数据从内核缓冲区复制到了应用层缓冲区，数据的接收靠内核（TCP协议栈）完成的
		ret = ::recv(clientfd, buff, sizeof(buff), 0);
		//recv返回值有3种情况，都要进行判断
		if(ret == -1) {
			ERROR_EXIT("recv");
			close(clientfd);
			return;
		} else if(ret == 0) {//连接断开
			close(clientfd);
		} else {//接收到了数据
			cout << " >> client receive " << ret << " bytes data." << endl;
			cout << " >> receive data: " << buff << endl;
		}
	}

	//6. 断开连接
	::close(clientfd);
}


int main(void)
{
	client_test();
	return 0;
}
