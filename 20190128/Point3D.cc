 ///
 /// @file    Point3D.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-21 15:31:41
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	int getY() const
	{
		return _iy;
	}
protected:
	int _ix;//对其派生类开放
private:
	int _iy;//私有成员只能在本类内部进行访问
};

class Point3D
: public Point//public继承 ------》接口继承
{
public:
	Point3D(int ix = 0, int iy = 0, int iz = 0)
	: Point(ix,iy)
	, _iz(iz)
	{
		cout << "Point(int,int,int)" << endl;
	}

	void display() const
	{
		cout << "(" << _ix //基类protected成员在派生类内部可以访问
			<< "," << _iy	//基类private成员在派生类中无法访问 需要在基类中定义一个public型的函数来返回
			<< "," << _iz << endl;
	}

private:
	int _iz;
};


class Point3D
: protected Point//protected继承
{
public:
	Point3D(int ix = 0, int iy = 0, int iz = 0)
	: Point(ix,iy)
	, _iz(iz)
	{
		cout << "Point(int,int,int)" << endl;
	}

	void display() const
	{
		cout << "(" << _ix //基类protected成员在派生类内部可以访问 其访问权限都是protected型的
			<< "," << _iy	//基类private成员在派生类中无法访问 需要在基类中定义一个public型的函数来返回
			<< "," << _iz 
			<< "," << getY() << endl; //基类的非私有成员，采用protected继承时，在派生类内部它的访问权限都是protected型的
	}

private:
	int _iz;
};


class Point3D
: private Point//private继承 ------》实现继承
{
public:
	Point3D(int ix = 0, int iy = 0, int iz = 0)
	: Point(ix,iy)
	, _iz(iz)
	{
		cout << "Point(int,int,int)" << endl;
	}

	void display() const
	{
		cout << "(" << _ix //基类protected成员在派生类内部可以访问 其访问权限都是private型的
			<< "," << _iy	//基类private成员在派生类中无法访问 需要在基类中定义一个public型的函数来返回
			<< "," << _iz 
			<< "," << getY() << endl; //基类的非私有成员，采用private继承时，在派生类内部它的访问权限都是private型的
	}

private:
	int _iz;
};
int main(void)
{
	Point3D pt3d;
	pt3d._ix;//对于基类非公有成员派生类对象都无法访问
	pt3d.getY();//对于派生类对象而言，只能访问基类的public公有成员
	return 0;
}
