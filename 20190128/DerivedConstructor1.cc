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
};


class Derived
: public Base
{
public:
	Derived(double derived)
	: _derived(derived)
	{
		cout << "Derived(double)" << endl;
	}
private:
	double _derived;
};
int main(void)
{
	Derived d(11.11);
	return 0;
}
