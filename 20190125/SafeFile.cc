 ///
 /// @file    SafeFile.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-11 11:22:09
 ///
 
#include <iostream>
#include <string>
#include <stdio.h>
using std::cout;
using std::endl;
using std::string;

class SafeFile
{
public:
	SafeFile(FILE * fp)
	: _fp(fp)
	{
		cout << "SafeFile(FILE *)" << endl;
		if(_fp == nullptr) {
			cout << "_fp == nullptr" << endl;
		}
	}

	void write(const string & msg)
	{
		fwrite(msg.c_str(),1,msg.size(),_fp);
	}

	~SafeFile()
	{
		cout << "~SafeFile()" << endl;
		if(_fp) {
			fclose(_fp);
			cout << "fclose(_fp)" << endl;
		}
	}
private:
	FILE * _fp;	
};
int main(void)
{
	//SafeFile sf(fopen("test.txt", "r"));
	SafeFile sf(fopen("test.txt", "w"));
	sf.write("hello,world\n");
	return 0;
}
