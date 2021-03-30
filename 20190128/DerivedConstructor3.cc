 ///
 /// @file    DerivedConstructor1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-21 17:40:18
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

	explicit
	Base(double base)
	: _base(base)
	{
		cout << "Base(double)" << endl;
	}
private:
	double _base;
};


class Derived
: public Base
{
public:
	Derived(double derived,double base)
	: _derived(derived)
	, Base(base)
	{
		cout << "Derived(double,double)" << endl;
	}
private:
	double _derived;
};
int main(void)
{
	Derived d(22.22,11.11);
	return 0;
}
