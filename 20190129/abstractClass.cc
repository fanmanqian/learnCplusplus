 ///
 /// @file    abstractClass.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 14:47:07
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class A
{
protected:
	A()
	{
		cout << "A()" << endl;
	}
};
class B
: public A
{
public:
	B()
	: A()
	{
		cout << "B()" << endl;
	}
};
int main(void)
{
	A a; 
	//B b;
	return 0;
}
