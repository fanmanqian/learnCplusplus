 ///
 /// @file    multiDerived1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-21 14:56:34
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	void display()const
	{
		cout << "A::display" << endl;
	}
};

class B
{
public:
	void show()const
	{
		cout << "B::show" << endl;
	}
};

class C
: public A
, public B
{

};

int main(void)
{
	C c;
	c.display();
	c.show();
	return 0;
}
