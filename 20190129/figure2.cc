 ///
 /// @file    figure1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 14:33:52
 ///
 
#include <math.h>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using std::function;
 
class Figure
{
public:
	using DisplayCallback = function<void()>;
	using AreaCallback = function<double()>;
	//注册回调函数
	void setDisplayCallback(DisplayCallback && dc)
	{
			_displayCallback = std::move(dc);
	}

	void setAreaCallback(AreaCallback && ac)
	{
		_areaCallback = std::move(ac);
	}

	//执行回调函数
	void handleDisplayCallback() const
	{
		if(_displayCallback) {
			_displayCallback();
		}
	}

	double handleAreaCallback() const
	{
		if(_areaCallback) {
			return _areaCallback();
		}
		else {
			return 0;
		}
	}

	DisplayCallback _displayCallback;
	AreaCallback _areaCallback;
};

void display(const Figure & fig)
{
	fig.handleDisplayCallback();
	cout << "'s area is ";
	cout << fig.handleAreaCallback();
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

	void show()
	{
		cout << "Circle";
	}

	double getArea()
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

	void print()
	{
		cout << "Triangle";
	}
	
	double get_Area()
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
	Figure fig;
	fig.setDisplayCallback(std::bind(&Rectangle::display,&rec));
	fig.setAreaCallback(std::bind(&Rectangle::area,&rec));
	display(fig);


	fig.setDisplayCallback(std::bind(&Circle::show,&cir));
	fig.setAreaCallback(std::bind(&Circle::getArea,&cir));
	display(fig);


	fig.setDisplayCallback(std::bind(&Triangle::print,&tri));
	fig.setAreaCallback(std::bind(&Triangle::get_Area,&tri));
	display(fig);
	return 0;
}
