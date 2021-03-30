 ///
 /// @file    multiDerived.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-25 10:47:41
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class A
{
public:
	A() { cout << "A()" << endl; }
	void show()
	{
		cout << "A::show()" << endl;
	}
};

class B
{
public:
	B() { cout << "B()" << endl; }
	void display()
	{
		cout << "B::display()" << endl;
	}
};


class C
{
public:
	C() { cout << "C()" << endl; }
	void print()
	{
		cout << "C::print()" << endl;
	}
};

class D
: public A
, public B
, public C
{
public:
	D()
	: B()
	, A()
	, C()
	{
		cout << "D()" << endl;
	}
};
int main(void)
{
	D d;
	d.show();
	d.display();
	d.print();
	return 0;
}
