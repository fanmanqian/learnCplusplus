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
	A(double ia = 0)
	: _ia(ia)
	{
		cout << "A(double)" << endl;
	}

	void setA(double ia)
	{
		_ia = ia;
	}

	void display() const 
	{
		cout << "A::_ia = " << _ia << endl;
	}

private:
	double _ia;
};

class B
: virtual public A
{
};

class C
: virtual public A
{

};

class D
: public B
, public C
{

};
int main(void)
{
	cout << "sizeof(A) = " << sizeof(A) << endl; 
	cout << "sizeof(B) = " << sizeof(B) << endl; 
	cout << "sizeof(C) = " << sizeof(C) << endl; 
	cout << "sizeof(D) = " << sizeof(D) << endl; 
	D d;
	d.setA(1);
	d.display();
	d.B::setA(100);
	d.B::display();
	d.C::setA(10);
	d.C::display();

	return 0;
}
