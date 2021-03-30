 ///
 /// @file    Complex.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-02 09:49:56
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 

class Complex
{
public:
	Complex(double dreal = 0, double dimag = 0) 
	: _dreal(dreal)
	, _dimag(dimag)
	{
		cout << "Complex(double,double)" << endl;
	}

	void print() const
	{
		cout << _dreal << "+" << _dimag << "i" << endl;
	}
	
	double getReal() const { return _dreal;}
	double getImag() const { return _dimag;}
	friend 
	Complex operator+(const Complex & lhs, const Complex & rhs);

public:
	double _dreal;
	double _dimag;//i^2 = -1 欧拉公式
};

Complex operator+(const Complex & lhs, const Complex & rhs)
{
	cout << "Complex operator+(const Complex&,const Complex&);" << endl;
	return Complex(lhs._dreal + rhs._dreal, lhs._dimag + rhs._dimag);
}

int main(void)
{
	Complex c1(1, 2);
	cout << "c1=";
	c1.print();
	Complex c2(3, 4);
	cout << "c2=";
	c2.print();
	Complex c3 = c1 + c2;
	cout << "c3=";
	c3.print();
	return 0;
}
