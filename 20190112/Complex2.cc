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
		if(_dreal==0&&_dimag==0){
			cout << 0 << endl;
		}
		else if(_dreal==0){
			cout << _dimag << "i" << endl;
		}
		else {
			cout << _dreal;
			if(_dimag > 0)
			{
				cout << "+" << _dimag << "i" << endl;
			}
			else if(_dimag < 0)
			{
				cout << "-" << (-1) * _dimag << "i" << endl;
			}
			else {
				cout <<  endl;
			}
		}
	}
	
	double getReal() const { return _dreal;}
	double getImag() const { return _dimag;} 
	Complex operator+(const Complex & rhs)
	{
		cout << "Complex operator+(const Complex & rhs)" << endl;
		return Complex(_dreal + rhs._dreal, _dimag + rhs._dimag);
	}
	
	Complex & operator+=(const Complex & rhs)
	{
		cout << "Complex & operator+=(const Complex & rhs)" << endl;
		_dreal = _dreal + rhs._dreal;
		_dimag = _dimag + rhs._dimag;
		return *this;
	}
    //前置++.后置++的区别
	//1.前置++的返回值为引用 其效率更高
	//  后置++的返回值为对象
	//  前置++可以取地址
	//  后置++返回的是临时对象 不能取地址
	Complex & operator++()
	{
		cout << "Complex & operator++()" << endl;
		++_dreal;
		++_dimag;
		return *this;
	}

	Complex operator++(int) //int参数没有实际意义，只是用来与前置++区分开来 后置++
	{
		Complex tmp(*this);
		++_dreal;
		++_dimag;
		return tmp;
	}

public:
	double _dreal;
	double _dimag;//i^2 = -1 欧拉公式
};


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
	c1 += c2;
	cout << "c1=";
	c1.print();
	cout << "++c1 = ";
	(++c1).print();
	cout << "c1 = ";
	c1.print();
	cout << "c1++ = ";
	(c1++).print();
	cout << "c1 = ";
	c1.print();
	return 0;
}
