 ///
 /// @file    oversee.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-25 11:07:14
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
	, _value(base)
	{
		cout << "Base(double)" << endl;
	}
	void display(int idx)
	{
		cout << "Base::display" << endl;
		cout << "Base::idx = " << idx << endl;
	}
private:
	double _base;
protected:
	double _value;
};


class Derived
: public Base
{
public:
	Derived(double base,double derived)
	: Base(base)
	, _derived(derived)
	, _value(derived)
	{
		cout << "Derived(double,double)" << endl;
	}
	void display()
	{
		cout << "Derived::display" << endl
			 << "Base::_value = " << _value << endl//隐藏: 派生类隐藏基类同名数据成员
			 << "Base::_value = " << Base::_value << endl
			 << "Derived::_value = " << _value << endl;
	}
private:
	double _derived;
	double _value;
};
int main(void)
{
	Derived d(11.11,22.22);
	//d.display(1); // 隐藏: 派生类隐藏基类的同名函数(改造基类成员)
	//d.Base::display(1);//通过类名可以解除这种隐藏
	d.display();
	return 0;
}
