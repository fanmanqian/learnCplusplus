 ///
 /// @file    virtualFunction4.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 13:15:37
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Base
{
public:
	Base()
	{
		cout << "Base()" << endl;
	}

	virtual 
	void func1()
	{
		cout << "Base::func1" << endl;
	}

	virtual
	void func2()
	{
		cout << "Base::func2" << endl;
	}

	~Base()
	{
		cout << "~Base()" << endl;
	}
};

class Middle
: public Base
{
public:
	Middle()
	:Base()
	{
		cout << "Middle()" << endl;
		func1();
	}
		
	virtual 
	void func1()
	{
		cout << "Middle::func1" << endl;
	}

	virtual
	void func2()
	{
		cout << "Middle::func2" << endl;
	}

	~Middle()
	{
		cout << "~Middle()" << endl;
		func2();
	}
};

class Derived
: public Middle
{
public:
	Derived()
	:Middle()
	{
		cout << "Derived()" << endl;
		func1();
	}
		
	virtual 
	void func1()
	{
		cout << "Derived::func1" << endl;
	}

	virtual
	void func2()
	{
		cout << "Derived::func2" << endl;
	}

	~Derived()
	{
		cout << "~Derived()" << endl;
		func2();
	}
};

int main(void)
{
	Derived d;
	return 0;
}
