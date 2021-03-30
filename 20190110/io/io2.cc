 ///
 /// @file    io2.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-23 08:32:46
 ///
 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
using std::ofstream;
using std::cin;
using std::fstream;


void test0()
{
	ifstream ifs;
	ifs.open("io1.cc");//对于文件输入流而言，打开的文件必须是存在的
	if(!ifs.good()){
		cout << "FILE CAN NOT OPEN" << endl;
	}
	vector<string> lines;
	string str;
	//while(ifs >> str)//输入流运算符默认以空格进行分隔
	while(getline(ifs,str))//获取一行数据
	{
		cout << str << endl;
		lines.push_back(str);
	}

	for(size_t idx = 0; idx != lines.size(); ++idx)
	{
		cout << lines[idx] << endl;
	}
	ifs.close();
}


void test1()
{
	ifstream ifs("io1.cc");
	if(!ifs) {
		cout << "FILE CAN NOT OPEN" << endl;
	}
	string file("test.txt");
	//文件不存在的时候，创建文件 
	//文件存在，则直接清空文件原来的内容，然后再重新写入
	ofstream ofs(file);
	if(!ofs){
		cout << "ofstream can not open" << endl;
		ifs.close();
	}
	string str;
	while(getline(ifs,str))
	{
		ofs << str << "\n";
	}
	ofs.close();
}

void printFsStatus(fstream & fs)
{
	cout << "fs's badbit" << fs.bad() << endl;
	cout << "fs's failbit" << fs.fail() << endl;
	cout << "fs's eofbit" << fs.eof() << endl;
	cout << "fs's goodbit" << fs.good() << endl;
}
void test2()
{
	string file("test2.txt");
	fstream fs(file);
	if(!fs){
		cout << "fs can open " << file << "error!" << endl;
		return ;
	}
	int number;
	for(size_t idx = 0; idx!=10; ++idx)
	{
		cin >> number;
		fs << number << " "; //文件输入流的功能
	}
	cout << ">> 文件写入已结束 number = " << number << endl;
	number = -1;
	cout << ">> number = " << number << endl;
	cout << ">> 查看流fs的状态: " << endl;
	//printFsStatus(fs);
	size_t pos = fs.tellg();
	
	//fs.seekg(0);
	fs.seekg(0, std::ios::beg);//std::ios::end std::ios::cur
	for(size_t idx = 0; idx!= 10; ++idx)
	{
		fs >> number;//文件输出流的功能
		cout << endl;
	//	printFsStatus(fs);
		cout << number << " ";
	}
	cout << endl;
}


void test3()
{

	string file("test.txt");
	//文件不存在的时候，创建文件 
	//文件存在，则直接清空文件原来的内容，然后再重新写入
	ofstream ofs(file,std::ios::app);//app是针对于输出流而言
	size_t pos = ofs.tellp();

	if(!ofs){
		cout << "ofstream can not open" << endl;
	}
	cout << "pos = " << pos << endl;
	ofs << "this is a new line\n";
	ofs.close();
}

void test4()
{
	ifstream ifs("io1.cc",std::ios::in|std::ios::ate);//直接定位到文件末尾 ate模式针对输入流 
	if(!ifs) {
		cout << "FILE CAN NOT OPEN" << endl;
	}
	cout << ">> pos = " << ifs.tellg() << endl;
	ifs.seekg(0,std::ios::end);
	cout << ">> pos = " << ifs.tellg() << endl;
	ifs.close();
}
int main(void)
{
	test4();
	return 0;
}
