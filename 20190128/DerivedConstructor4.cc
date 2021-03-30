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
	Derived(double derived,double base,Base base2)
	: Base(base) //对于基类是用类名调用构造函数
	, _derived(derived)
	, _base(base2)//对于对象成员是用对象名调用构造函数
	{
		cout << "Derived(double,double,Base)" << endl;
	}
private:
	double _derived;
	Base _base;
};
int main(void)
{
	Base base2(33.33);
	Derived d(22.22,11.11,base2);
	return 0;
}
