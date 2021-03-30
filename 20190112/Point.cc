 ///
 /// @file    Point.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-02 08:45:41
 ///
#include <math.h> 
#include <iostream>
using std::cout;
using std::endl;
 
class Point
{
//友元不受访问权限的限制 位置可以随便放
	friend float distance(const Point & lhs, const Point & rhs);
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



float distance(const Point & lhs, const Point & rhs)
{
	//return sqrt(pow((lhs._ix - rhs._ix), 2) + pow((lhs._iy - rhs._iy),2));
	return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy);
}


int main(void)
{
	Point pt1(1, 2);
	Point pt2(3, 4);

	pt1.print();
	cout << "---->";
	pt2.print();
	cout << "的距离 " << distance(pt1, pt2) << endl;
	return 0;
}
