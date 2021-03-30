 ///
 /// @file    io3.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-23 11:05:20
 ///
 
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::string;
using std::ifstream;

void test0()
{
	int number1 = 10;
	int number2 = 20;


	stringstream ss;//字符串输出流功能
	ss << "number1= " << number1 << " ,number2= " << number2 << endl;
	//fprintf有点像
	string line = ss.str();
	cout << line << endl;
	string key;
	int value;
	//必须知道格式 才能准确解析
	//stringstream 没有close方法
	//字符串输入流的功能
	while(ss >> key >> value, !ss.eof())
	{
		cout << key << "----->" << value << endl;
	}
}
string int2str(int number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}


void test2()
{
	int value = 1024;
	string str = int2str(value);
	cout << "str = " << str << endl;
}


void readConfig(const char * filename)
{
	string file(filename);
	ifstream ifs(file);
	if(!ifs){
		cout << "ifstream open " << file << "error" << endl;
	}
	string key;
	string value;
	string line;
	while(getline(ifs,line)){
		istringstream iss(line);
		iss >> key >> value;
		cout << key << " ---> " << value << endl;
	}
	ifs.close();
}

void test33()
{
	readConfig("myConf");
}
int main(void)
{
	test33();
	return 0;
}
