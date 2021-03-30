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

};
int main(void)
{
	Derived d;
	return 0;
}
