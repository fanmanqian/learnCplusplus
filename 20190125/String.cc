 ///
 /// @file    String.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-11 09:54:56
 ///
 //

#include <string.h>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;


class String
{
public:
	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		cout << "String(const char *)" << endl;
		strcpy(_pstr,pstr);
	}

	~String()
	{
		if(_pstr)
		{
			cout << "~String()" << endl;
			delete [] _pstr;
		}
	}

	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(const String &)" << endl;
		strcpy(_pstr,rhs._pstr);
	}

//移动复制构造函数
	String(String && rhs)
	: _pstr(rhs._pstr)
	{
		cout << "String(String &&)" << endl;
		rhs._pstr = nullptr;
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &)" << endl;
		if(this != &rhs) {
			delete [] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr,rhs._pstr);
		}
		return *this;
	}
//移动赋值运算符函数
	String & operator=(String && rhs)
	{
		cout << "String & operator=(String &&)" << endl;
		if(this != &rhs) {
			delete [] _pstr;
			_pstr = rhs._pstr;
			rhs._pstr = nullptr;
		}
		return *this;
	}

	friend std::ostream & operator << (std::ostream & os,const String & rhs);
private:
	char * _pstr;
};

std::ostream & operator << (std::ostream & os,const String & rhs)
{
	os << rhs._pstr;
	return os;
}

template<class Container>
void display(const Container & c)
{
	for(auto & elem : c) {
		cout << elem << " ";
	}
	cout << endl;
}

int main(void)
{
//	vector<String> vec;
//	vec.push_back("hello,world");//调用移动复制构造
//	String s1 = "hello";
//	vec.push_back(s1);//调用复制构造函数
//	display(vec);
	String s2("hello");
	String s3 = std::move(s2);//std::move将左值转换成右值 在内部做强制转换 s2 = std::move(s2) 左右两侧地址值一样
							  //同时意味着s2以后不再使用了
	cout << "s3 = " << s3 << endl;
	cout << "s2 = " << s2 << endl;
	return 0;
}
