 ///
 /// @file    DerivedCopyControl1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-25 14:48:01
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class Base
{
public:
	Base()
	: _pstr(nullptr)
	{
		cout << "Base()" << endl;
	}

	Base(const char * pstr)
	: _pstr(new char[strlen(_pstr) + 1]())
	{
		cout << "Base(const char *)" << endl;
		strcpy(_pstr,pstr);
	}

	Base(const Base & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "Base(const Base & )" << endl;
		strcpy(_pstr,rhs._pstr);
	}

	Base & operator=(const Base & rhs)
	{
		cout << "Base & operator=(const Base &)" << endl;
		if(this != &rhs) {
			delete [] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr,rhs._pstr);
		}
		return *this;
	}
	
	~Base()
	{
		cout << "~Base()" << endl;
		if(_pstr) {
			delete [] _pstr;
		}
	}
	friend std::ostream & operator<<(std::ostream & os, const Base & rhs);
private:
	char * _pstr;
};


std::ostream & operator<<(std::ostream & os, const Base & rhs)
{
	os << rhs._pstr;
	return os;
}


class Derived
: public Base
{
public:
	Derived(const char * base)
	: Base(base)
	{
		cout << "Derived(const char *,const char *)" << endl;
	}

	~Derived()
	{
		cout << "~Derived()" << endl;
	}
	friend std::ostream & operator<<(std::ostream & os,const Derived & rhs);
};


std::ostream & operator<<(std::ostream & os,const Derived & rhs)
{
	const Base & base = rhs;
	os << base;
	return os;
}

int main(void)
{
	Derived d1("hello");
	cout << "d1 = " << d1 << endl;
	Derived d2 = d1;
	cout << "d2 = " << d2 << endl;
	Derived d3("world");
	d1 = d3;
	cout << "d3 = " << d3 << endl;
	cout << "d1 = " << d1 << endl;
	return 0;
}
