 ///
 /// @file    virtualTable.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-27 13:39:11
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Base
{
public:
	Base():_base(10)
	{
		cout << "Base()" << endl;
	}

	virtual 
	void func1()
	{
		cout << "Base::func1()" << endl;
	}

	virtual
	void func2()
	{
		cout << "Base::func2()" << endl;
	}
private:
	long _base;
};

class Derived
: public Base
{
public:
	Derived()
	: _derived(100)
	{
		cout << "Derived()" << endl;
	}

	void func1()
	{
		cout << "Derived::func1()" << endl;
	}
	
	void func2()
	{
		cout << "Derived::func2()" << endl;
	}

private:
	long _derived;
};

int main(void)
{
	Derived d;
	long ** p = (long**)&d;
	typedef void(*Function)(void);
	Function f1;
	f1 = (Function)p[0][0];
	f1();
	Function f2;
	f2 = (Function)p[0][1];
	f2();
	cout << (long)*(p+1) << endl;
	cout << "_base = " << (long)p[1] << endl;
	cout << "_derived = " << (long)p[2] << endl;

	return 0;
}
