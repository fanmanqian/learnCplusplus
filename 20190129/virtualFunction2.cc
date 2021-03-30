 ///
 /// @file    virtualFunction2.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 09:23:01
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Base
{
public:
	Base(): _dbase(0)
	{ cout << "Base()" << endl; }

	virtual 
	void display() const
	{ cout << "Base::display _dbase = " << _dbase << endl; }

private:
	double _dbase;
};

class Derived
: public Base
{
public:
	Derived():_derived(10)
	{ cout << "Derived()" << endl; }

	void display() const override
	{ cout << "Derived::display _derived = " << _derived << endl; }

private:
	double _derived;
};

//引用也能体现多态机制
void display(Base & base)
{
	base.display();//同一个指令，针对不同的对象，产生不同的行为
}

int main(void)
{
	Base base;
	Derived derived;
	base.display();//当采用对象名，进行访问的时候，并不体现多态特性，采用的是静态联编
	derived.display();//隐藏 直接去程序代码区中查找函数
	return 0;
}
