 ///
 /// @file    TestConnection.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-07 18:26:19
 ///
 
#include "Threadpool.h"
#include "TcpConnection.h"
#include "TcpServer.h"
#include "Dict.h"
#include <unistd.h>
#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;
using std::string;
using namespace wd;


class MyTask
{
public:
	MyTask(const string & request, shared_ptr<TcpConnection> conn,Dict dict)
	: _request(request)
	, _conn(conn)
	, _dict(dict)
	{}

	//process方法是线程池中的子线程来执行的
	void process()
	{
		//....do something
		//decode compute encode
		vector<string> response = doTask();//业务逻辑处理
		for(auto & elem : response) {
			_conn->sendInLoop(response);//不能直接发送 因为现在处于计算线程 并不在IO线程
		}//这里涉及线程间通信 
	}

	vector<string> doTask()
	{
		string response;
		if(_request.size()==0) {
			response = "what do you mean.";
		}
		else {
			for(string::size_type col = 0; col < _request.size(); ++col) {
				string sing = _request.substr(col,1);
				if(vec.size() < 5) queryIndex(sing);
				else if(vec.size()==5){
					break;
				}
			}
		}

		return vec;
	}
	
	void queryIndex(const string & sing)
	{
		_dict.genDict();
		_dict.genIndex();
		map<string,set<int>> mp = _dict.getIndex();
		vector<pair<string,int>> vec = _dict.getVec();
		set<int> st = mp[sing];
		for(auto & elem : st) {
			int dis = getDis(vec[elem].first);
			if(vec.size() < 5 && dis < 5) {
				vec.push_back(vec[elem].first);
			}
		}
	}

private:
	string _request;
	shared_ptr<TcpConnection> _conn;
	Dict & _dict;
	vector<string> vec;
};
void onConnection(const shared_ptr<wd::TcpConnection> & conn)
{
	cout << ">>> " << conn->toString() << " has connected!" << endl;
}

void onMessage(const shared_ptr<wd::TcpConnection> & conn) 
{
	string msg = conn->receive();
	cout << ">> server receive: " << msg << endl;
	//...do something //处理时间不宜过长1ms 1ns 1ws
	//
	//decode 
	//compute //当处理业务逻辑的时间过长时 必须引入线程池 ----> 引入线程池
	//encode
	const string _loc1 = "../GenDict/The_Holy_Bible.txt";
	const string _loc2 = "../GenDict/output.dat";
	Dict dic(_loc1,_loc2);
	MyTask task(msg,conn,dic);
	unique_ptr<Threadpool> threadpoolPtr(new Threadpool(4,10));
	threadpoolPtr->start();
	threadpoolPtr->addTask(std::bind(&MyTask::process,task));
	threadpoolPtr->stop();
	//pthreadpool->addTask(std::bind(&MyTask::process,task));
	//不能再直接发送数据了
	//conn->send(msg);
	
}

void onClose(const shared_ptr<wd::TcpConnection> & conn)
{
	cout << ">>> " << conn->toString() << " has closed!!!!" << endl;
}


void test0()
{

/*	wd::Acceptor acceptor("192.168.146.144",8888);
	acceptor.ready();
	
	wd::EventLoop loop(acceptor);

	loop.setConnectionCallback(onConnection);
	loop.setMessageCallback(onMessage);
	loop.setCloseCallback(onClose);
	loop.loop();*/
#if 0
	int peerfd = acceptor.accept();

	wd::TcpConnection conn(peerfd);
	string msg = conn.receive();
	cout << " >> server receive : " << msg << endl;
	conn.send(msg);
	::sleep(2);
#endif
	wd::TcpServer server("192.168.146.144",8888);
	server.setConnectionCallback(onConnection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);
	server.start();
}
int main(void)
{
	test0();
	return 0;
}
