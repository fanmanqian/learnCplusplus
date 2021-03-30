 ///
 /// @file    typecast.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-25 14:23:40
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
	
	void display() const
	{
		cout << "Base::display" << endl
			 << "_base = " << _base << endl;
	}
private:
	double _base;
};

class Derived
: public Base
{
public:
	Derived()
	:Base()
	{
		cout << "Derived()" << endl;
	}

	Derived(double base,double derived)
	: Base(base)
	, _derived(derived)
	{
		cout << "Derived(double,double)" << endl;
	}

	void print() const
	{
		cout << "Derived::print" << endl
			// << "_base = " << _base << endl;
			 << "_derived = " << _derived << endl;
	}

private:
	double _derived;
};


int main(void)
{
	Derived d(11.11,22.22);
	d.print();
	Base base(13);
	base.display();
	base = d;
	base.display();

	Base & base2 = d;
	base2.display();
	
	Base * base3 = &d;
	base3->display();
	return 0;
}
