 ///
 /// @file    tcp_server.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-09 16:14:47
 ///

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define ERROR_EXIT(msg) do{\
	::perror(msg);\
	::exit(EXIT_FAILURE);\
}while(0)

struct thread_data{
	const char * ip;
	unsigned short port;
	int peerfd;
};

struct thread_data pth_data;

void * process_connection(void * arg)
{
	struct thread_data * pth_data = (struct thread_data *)arg;
	string ip(pth_data->ip);
	unsigned short port = pth_data->port;
	int peerfd = pth_data->peerfd;
	struct sockaddr_in clientaddr;//4.1 解析对端Ip和Port
	::memset(&clientaddr, 0, sizeof(struct sockaddr_in));
	socklen_t len = sizeof(struct sockaddr_in);
	int ret = ::getpeername(peerfd, (struct sockaddr *)(&clientaddr), &len);
	string clientip(inet_ntoa(clientaddr.sin_addr));//二进制的地址转换为点分十进制的ip地址
	unsigned short clientport = ntohs(clientaddr.sin_port);//大端模式转换为小端模式
	cout << ">>>>subthread " << pthread_self() << " >>>> server " << ip << ":" << port
		 << " --> " << " client " << clientip << ":" << clientport
		 << " has connected!" << endl;
	//5. 进行数据的接收和发送
	
	char buff[1024] = {0}; //应用层接收缓冲区
//	cout << "before recv" << endl;
	ret = ::recv(peerfd, buff, sizeof(buff), 0);//默认情况下是一个阻塞式函数 peerfd上发生了读事件
//	cout << "after recv" << endl;
	if(ret == -1) {
		if(ret == -1 && errno == EINTR)
			return nullptr;
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
		cout << " >>>> server gets msg from client : " << buff << endl;
		//7. 进行数据的发送，回显操作
		ret = ::send(peerfd,buff,strlen(buff),0);//peerfd上发生了写事件 
		if(ret == -1) {
			ERROR_EXIT("send");
			::close(peerfd); 
		}
		//8. 断开连接
		::close(peerfd); //关闭连接,回收文件描述符 
	}
}


int test0() 
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
	serveraddr.sin_addr.s_addr = inet_addr(ip.data());//把点分十进制地址转换为32位二进制地址
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
	vector<pthread_t> pthreads;
	//并发服务器模型之多线程模型: 一个请求交给一个子线程处理
	int cnt = 5;
	while(cnt--) {
		//4. 建立新连接
		cout << " >> server is about to accept new link " << endl;
		int peerfd = ::accept(listenfd,NULL,NULL);//在listenfd上是有读事件发生的
		if(peerfd == -1) {
			::close(listenfd);
			ERROR_EXIT("accept");
		}
		pth_data.ip = ip.data();
		pth_data.port = port;
		pth_data.peerfd = peerfd;
		cout << " >> server serve client with peerfd = " << peerfd << endl;
		pthread_t pthid;
		if(pthread_create(&pthid,NULL,process_connection,(void *)&pth_data)) {
			ERROR_EXIT("pthread_create");
		}
		pthreads.push_back(pthid);
		cout << " >>main thread create subthread " << pthid << endl;
	} // end of while
	cout << " >>main thread release threads..." << endl;
	for(auto & item : pthreads) {
		pthread_join(item,NULL);
	}
	//9. 关闭服务器的监听的文件描述符
	::close(listenfd);//文件描述符资源是有限的
}


int main(void)
{
	test0();
	return 0; 
}
