 ///
 /// @file    figure1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 14:33:52
 ///
 
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;
 
class Figure
{
public:
	virtual 
	void display() = 0;

	virtual
	double area() = 0;
};

void display(Figure & fig)
{
	fig.display();
	cout << "'s area is ";
	cout << fig.area();
	cout << endl;
}

class Rectangle
: public Figure
{
public:
	Rectangle(double length,double width)
	: _length(length)
	, _width(width)
	{

	}

	void display()
	{
		cout << "Rectangle";
	}

	double area()
	{
		return _length * _width;
	}

private:
	double _length;
	double _width;
};

class Circle
: public Figure
{
public:
	Circle(double radius)
	: _radius(radius)
	{}

	void display()
	{
		cout << "Circle";
	}

	double area()
	{
		return PI * _radius * _radius;
	}

private:
	double _radius;
	static const double PI;
};
const double Circle::PI = 3.14159;

class Triangle
: public Figure
{
public:
	Triangle(double a,double b,double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{}

	void display()
	{
		cout << "Triangle";
	}
	
	double area()
	{
		double p = (_a + _b + _c) / 2;
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}
private:
	double _a;
	double _b;
	double _c;
};


int main(void)
{
	Rectangle rec(4,5);
	Circle cir(3);
	Triangle tri(3,4,5);
	display(rec);
	display(cir);
	display(tri);
	return 0;
}
