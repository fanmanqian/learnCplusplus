 ///
 /// @file    TestConnection.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 18:26:19
 ///
 
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;
 
void test0()
{
	wd::Acceptor acceptor("192.168.146.144",8888);
	acceptor.ready();
	
	wd::EventLoop loop(acceptor);

	loop.loop();
#if 0
	int peerfd = acceptor.accept();

	wd::TcpConnection conn(peerfd);
	string msg = conn.receive();
	cout << " >> server receive : " << msg << endl;
	conn.send(msg);
	::sleep(2);
#endif
}
int main(void)
{
	test0();
	return 0;
}
