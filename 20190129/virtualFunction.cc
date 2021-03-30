 ///
 /// @file    virtualFunction.cc
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

	void display() const
	{ cout << "Derived::display _derived = " << _derived << endl; }

private:
	double _derived;
};

void display(Base * base)
{
	base->display();//同一个指令，针对不同的对象，产生不同的行为
}

int main(void)
{
	cout << "sizeof(Base) = " << sizeof(Base) << endl;//虚函数实现的关键 这里的值本来是8 但是现在变成了16
	Base base;
	Derived derived;//当传递基类的对象时，调用基类的display函数
	display(&base);//当传递的是派生类对象时，调用的是派生类的display函数
	display(&derived);
	return 0;
}
