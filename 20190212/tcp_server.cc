 ///
 /// @file    tcp_server.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-09 16:14:47
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
using std::string;

#define ERROR_EXIT(msg) do{\
	::perror(msg);\
	::exit(EXIT_FAILURE);\
}while(0)

void test0()
{
	//笔试题:写一个程序判断电脑的存储使用的是大端字节序还是小端字节序
	int a = 1;
	char * p = (char*)(&a);
	int b = (int)(*p);
	cout << "b = " << b << endl;
	p += 3;
	int c = (int)(*p);
	cout << "c = " << c << endl;
}

void test1()
{
	//笔试题:写一个程序判断电脑的存储使用的是大端字节序还是小端字节序
	union test{
		int a;
		char data[4];
	};
	test t1;
	t1.a = 1;
	int x = t1.data[0];
	int y = t1.data[3];

	cout << "t1.data[0]" << x << endl;
	cout << "t1.data[3]" << y << endl;
}

int test2() 
{
	//1. 创建套接字，得到一个文件描述符
	int listenfd = ::socket(AF_INET,SOCK_STREAM,0);//TCP协议
	if(listenfd == -1) {
		//::perror("socket");
		//::exit(EXIT_FAILURE);
		ERROR_EXIT("socket");
	}
	//网络地址 ===> 采用大端模式
	unsigned short port = 8888;
	string ip("192.168.146.144");
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);//小 ==》大
	//下面这样写是不行的 这就牵扯到网络字节序和主机字节序 或者说是
	//大端模式和小端模式
	//addr.sin_addr = "192.168.146.144";
	//大端模式  小端模式
	//网络字节序  主机字节序见20190212的笔记
	serveraddr.sin_addr.s_addr = inet_addr(ip.data());
	//2. 绑定
	if(-1 == ::bind(listenfd,(const struct sockaddr *)&serveraddr,sizeof(serveraddr))) {
		//::perror("bind");
		//::exit(EXIT_FAILURE);
		::close(listenfd);
		ERROR_EXIT("socket");
	}

	//3. listen对新连接请求进行监听
	if(-1 == ::listen(listenfd,10)) {//设置处于半连接状态的连接数的最大值
		::close(listenfd);
		ERROR_EXIT("listen");
	}
	//并发服务器模型之 循环（迭代）服务器
	while(1) {
		//4. 建立新连接
		cout << " >> server is about to accept new link " << endl;
		int peerfd = ::accept(listenfd,NULL,NULL);
		if(peerfd == -1) {
			::close(listenfd);
			ERROR_EXIT("accept");
		}
		//如果peerfd > 0,则新连接建立完毕，以后通过peerfd对应的数据结构与
		//对端进行通信
		
		//peerfd//代表的就是一个建立好的连接，满足五元组
		//100-107未测试通 可以不看
//		struct sockaddr_in clientaddr;//4.1 解析对端Ip和Port
//		socklen_t len = 0;
//		int ret = ::getpeername(peerfd, (struct sockaddr *)(&clientaddr), &len);
//		string clientip(inet_ntoa(clientaddr.sin_addr));
//		unsigned short clientport = ntohs(clientaddr.sin_port);
//		cout << " >>> server " << ip << ":" << port
//			 << " --> " << " client " << clientip << ":" << clientport
//			 << " has connected!" << endl;
		//5. 进行数据的接收和发送
		
		char buff[1024] = {0}; //应用层接收缓冲区
		cout << "before recv" << endl;
		int ret = ::recv(peerfd, buff, sizeof(buff), 0);//默认情况下是一个阻塞式函数
		cout << "after recv" << endl;
		if(ret == -1) {
			if(ret == -1 && errno == EINTR)
				continue;
			else 
				ERROR_EXIT("recv");
		} 
		else if(ret == 0) { //连接已经断开了
			::close(peerfd);
		} 
		else {
		//ret表示已经接收到了的对端数据的长度
		//6. 对接收的数据进行处理（业务逻辑）
		//....
		cout << " >> server gets msg from client : " << buff << endl;
		//7. 进行数据的发送，回显操作
		ret = ::send(peerfd,buff,strlen(buff),0);
		if(ret == -1) {
			ERROR_EXIT("send");
			::close(peerfd); 
		}
		//8. 断开连接
		::close(peerfd); //关闭连接 
		}
	} // end of while
	//9. 关闭服务器的监听的文件描述符
	::close(listenfd);//文件描述符资源是有限的
}
int main(void)
{
	//test0();
	//test1();
	test2();
	return 0; 
}
