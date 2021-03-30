 ///
 /// @file    String.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-11 08:58:05
 ///

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
 
class String
{
public:
	String()
	: _pstr(new char[1]())
	{
		cout << "String()" << endl;
	}

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr,pstr);
		cout << "String(const char *)" << endl;
	}

	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		strcpy(_pstr,rhs._pstr);
		cout << "String(const String &)" << endl;
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &)" << endl;
		if(this!=&rhs)
		{
			delete [] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr,rhs._pstr);
		}
		return *this;
	}

	~String()
	{
		cout << "~String()" << endl;
		if(_pstr)
			delete [] _pstr;
	}

	void print() const
	{
		if(_pstr)
		{
			cout << _pstr << endl;
		}else
		{
			cout << "空串" << endl;
		}

	}
private:
	char * _pstr;
};
int main(void)
{
	String s1;
	s1.print();
	String s2("hello world");
	s2.print();
	String s3 = s2;
	s3.print();
	s1 = s3;
	s1.print();
	return 0;
}
