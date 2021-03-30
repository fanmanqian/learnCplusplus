 ///
 /// @file    figure.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-01-29 15:56:09
 ///
 
#include <math.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

//面向对象设计原则：
//	对扩展开放，对修改关闭
//
//	动态多态的实现： 继承 + 虚函数
class Figure
{
public:
	virtual void display() const=0;
	virtual double area()=0;

	virtual ~Figure() {cout << "~Figure()" << endl;	}
};

void display(Figure & fig) 
{
	fig.display();
	cout << "'s area is " << fig.area() << endl; 
}

class Rectangle
: public Figure
{
public:
	Rectangle(double length, double width)
	: _length(length)
	, _width(width)
	{}

	void display() const override
	{	cout << "rectangle";}

	double area() override
	{
		return _length * _width;
	}

	~Rectangle() {	cout << "~Rectangle()" << endl;	}
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

	void display() const override
	{	cout << "circle";}

	double area() override
	{
		return PI * _radius * _radius;
	}

	~Circle() {	cout << "~Circle()" << endl;	}
private:
	double _radius;
	static const double PI;
};

const double Circle::PI = 3.14159;

class Triangle 
: public Figure
{
public:
	Triangle(double a, double b, double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{}

	void display() const override
	{	cout << "triangle";}

	double area() override
	{
		double p = (_a + _b + _c) / 2;
		return sqrt(p *(p - _a) * (p -_b) * (p- _c));
	}

	~Triangle(){	cout << "~Triangle()" << endl;	}
private:
	double _a;
	double _b;
	double _c;
};

//简单工厂模式/静态工厂方法
//面向对象设计原则:
//1.违反了开放闭合原则
//2.单一职责原则

class Factory
{
public:
	virtual Figure * create()=0;

	virtual ~Factory(){cout << "~Factory()" << endl;	}
};

class RectangleFactory
: public Factory
{
public:
	Figure * create()
	{
		//load xml
		//parse xml
		//get parameter
		return new Rectangle(10, 11);
	}

	~RectangleFactory() {	cout << "~RectangleFactory()" << endl;	}
};

class CircleFactory
: public Factory
{
public:
	Figure * create()
	{
		//load xml
		//parse xml
		//get parameter
		return new Circle (5);
	}

	~CircleFactory(){	cout << "~CircleFactory()" << endl;	}
};

class TriangleFactory
: public Factory
{
public:
	Figure * create()
	{
		//load xml
		//parse xml
		//get parameter
		return new Triangle(3, 4, 5);
	}

	~TriangleFactory(){ cout << "~TriangleFactory()" << endl;	}
};

int main(void)
{
	Rectangle(3, 4);//对于简单对象来说，是没有必要使用工厂模式

	//工厂模式是针对于复杂对象, 批量对象
	unique_ptr<Factory> rectangleFactory(new RectangleFactory());
	unique_ptr<Figure> rectangle(rectangleFactory->create());

	unique_ptr<Factory> circleFactory(new CircleFactory());
	unique_ptr<Figure> circle(circleFactory->create());

	unique_ptr<Factory> triangleFactory(new TriangleFactory());
	unique_ptr<Figure> triangle(triangleFactory->create());

	display(*rectangle);
	display(*circle);
	display(*triangle);

	return 0;
}
