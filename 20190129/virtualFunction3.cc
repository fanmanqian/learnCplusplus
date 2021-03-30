 ///
 /// @file    virtualFunction3.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 12:35:04
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Base
{
public:
	Base()
	: _dbase(0)
	{ cout << "Base()" << endl; }

	virtual
	void display() const 
	{
		cout << "Base::display _dbase = " << _dbase << endl; 
	}

	void func1()
	{
		display();
	}

	void func2()
	{
		Base::display();
	}

private:
	double _dbase;
};

class Derived
: public Base
{
public:
	Derived()
	: Base()
	, _derived(10)
	{
		cout << "Derived()" << endl;
	}

	void display() const override
	{
		cout << "Derived::display _derived = " << _derived << endl;
	}

private:
	double _derived;
};

int main(void)
{
	Derived d;
	Base b;
	Base * pBase = &b;
	pBase->func1();
	pBase->func2();
	pBase = &d;
	pBase->func1();
	pBase->func2();
	return 0;
}
