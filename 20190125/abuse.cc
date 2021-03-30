 ///
 /// @file    abuse.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 15:33:46
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;


class Point
: public std::enable_shared_from_this<Point>
{
public:
	Point(int ix,int iy)
	: _ix(ix)
	, _iy(iy)
	{ cout << "Point(int,int)" << endl; }

	void display() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

//	Point * addPoint(Point * pt)
//	{
//		_ix += pt->_ix;
//		_iy += pt->_iy;
//		return this;
//	}

	shared_ptr<Point> addPoint(Point * pt)
	{
		//在类内部获取本对象的shared_ptr智能指针
		_ix += pt->_ix;
		_iy += pt->_iy;
		return shared_ptr<Point>(this);//this是原生裸指针
		return shared_from_this();
	}

	~Point()
	{ cout << "~Point()" << endl; } 
private:
	int _ix;
	int _iy;
};
//第一种滥用
void test0()
{
	//将一个原生的裸指针交给不同的智能指针进行托管
	Point * pt = new Point(1,2);
	unique_ptr<Point> up1(pt);
	unique_ptr<Point> up2(pt);
}
//第二种滥用
void test1()
{
	unique_ptr<Point> up1(new Point(1,2));
	unique_ptr<Point> up2(new Point(3,4));
	up2.reset(up1.get());
}
//第三种滥用
void test2()
{
	shared_ptr<Point> up1(new Point(1,2));
	shared_ptr<Point> up2(new Point(3,4));
	shared_ptr<Point> up3(up1.get()->addPoint(up2.get()));
}
//第三种滥用的解决或者说是避免
//1、让Point类去继承std::enable_shared_from_this<Point>
//2、在类内部获取本对象的shared_ptr智能指针见类内部的addPoint函数
void test3()
{	
	shared_ptr<Point> up1(new Point(1,2));
	shared_ptr<Point> up2(new Point(3,4));
	shared_ptr<Point> up3(up1.get()->addPoint(up2.get()));
}
int main(void)
{
	//test0();
	//test1();
	//test2();
	test3();
	return 0;
}
