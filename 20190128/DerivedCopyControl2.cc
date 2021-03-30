 ///
 /// @file    DerivedCopyControl2.cc
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
	Derived(const char * base,const char * pdata2)
	: Base(base)
	, _pdata2(new char[strlen(pdata2 + 1)]())
	{
		cout << "Derived(const char *,const char *)" << endl;
		strcpy(_pdata2,pdata2);
	}
	
	Derived(const Derived & rhs)
	: Base(rhs)
	, _pdata2(new char[strlen(rhs._pdata2) + 1]())
	{
		cout << "Derived(const Derived &)" << endl;
		strcpy(_pdata2,rhs._pdata2);
	}

	Derived & operator=(const Derived & rhs)
	{
		cout << "Derived & operator=(const Derived & )" << endl;
		if(this != &rhs) {
			Base::operator=(rhs);
			delete [] _pdata2;
			_pdata2 = new char[strlen(rhs._pdata2) + 1]();
			strcpy(_pdata2,rhs._pdata2);
		}
		return *this;
	}

	~Derived()
	{
		cout << "~Derived()" << endl;
	}
	friend std::ostream & operator<<(std::ostream & os,const Derived & rhs);
private:
	char * _pdata2;
};


std::ostream & operator<<(std::ostream & os,const Derived & rhs)
{
	const Base & base = rhs;
	os << base << ","
	   << rhs._pdata2;
	return os;
}

int main(void)
{
	Derived d1("hello","world");
	cout << "d1 = " << d1 << endl;
	Derived d2 = d1;
	cout << "d2 = " << d2 << endl;
	Derived d3("hubei","wuhan");
	d1 = d3;
	cout << "d3 = " << d3 << endl;
	cout << "d1 = " << d1 << endl;
	return 0;
}
