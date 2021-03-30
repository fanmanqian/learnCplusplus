 ///
 /// @file    abstract.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 13:34:28
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class A
{//抽象类作为接口存在
public:
	virtual
	void display() = 0;//声明了纯虚函数的类是抽象类，抽象类不能创建对象

	virtual
	void print() = 0;
};

class B
: public A
{
public:
	//对于抽象类的派生类而言,只要有一个纯虚函数没有实现，那么该派生类也会成为抽象类
	void display()
	{
		cout << "B::display" << endl;
	}
};

class C
: public B
{
public:
	void print()
	{
		cout << "C::print()" << endl;
	}
};
int main(void)
{
	//B b;
	//A * a = &b;
	//a->display();
	C c;
	A * a = &c;
	a->print();
	return 0;
}
