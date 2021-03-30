 ///
 /// @file    destructor.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 14:51:22
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Base
{
public:
	Base()
	: _pdata(new int(10))
	{
		cout << "Base()" << endl;
	}


	virtual	
	~Base()
	{
		cout << "~Base()" << endl;
		if(_pdata) {
			delete _pdata;
		}
	}

private:
	int * _pdata;
};

class Derived
: public Base
{
public:
	Derived(int data)
	: Base()
	, _pdata2(new int(data))
	{
		cout << "Derived()" << endl;
	}


	~Derived()
	{
		cout << "~Derived()" << endl;
		if(_pdata2) {
			delete _pdata2;
		}
	}

private:
	int * _pdata2;
};


int main(void)
{
//	Derived d;
	Base * p = new Derived(100);
	delete p;
	return 0;
}
