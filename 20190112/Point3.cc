 ///
 /// @file    Point.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-02 08:45:41
 ///
#include <math.h> 
#include <iostream>
using std::cout;
using std::endl;
class Point;//类的前向声明

class Line{
public:
	float distance(const Point & lhs, const Point & rhs);//该函数声明不需要知道Point的实现
	void setPoint(Point & pt, int ix, int iy);
};


class Point
{
//友元不受访问权限的限制 位置可以随便放
	//friend float Line::distance(const Point & lhs, const Point & rhs);
	//friend class Line;
	friend Line;
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	void print() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

private:
	int _ix;
	int _iy;
};


float Line::distance(const Point & lhs, const Point & rhs)
{
	//return sqrt(pow((lhs._ix - rhs._ix), 2) + pow((lhs._iy - rhs._iy),2));
	return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy);
}

void Line::setPoint(Point & pt, int ix, int iy)
{
	pt._ix = ix;
	pt._iy = iy;
}
int main(void)
{
	Point();//匿名对象，临时对象
	Point pt1(1, 2);
	Point pt2(3, 4);

	pt1.print();
	cout << "---->";
	pt2.print();
	cout << "的距离 " << Line().distance(pt1, pt2) << endl;
	Line().setPoint(pt1,10,11);
	pt1.print();
	return 0;
}
