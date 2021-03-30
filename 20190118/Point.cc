 ///
 /// @file    Point.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 10:47:51
 ///
 
#include <iostream>
using std::cout;
using std::endl;
//全局类/普通类 
class Point
{
public:
	Point(double ix, double iy)
	: _ix(ix)
	, _iy(iy)
	{

	}
	//成员函数模板,模板参数可以设置默认值
	template<class T = int>
	T func()
	{
		return (T)_ix;
	}

	friend std::ostream & operator << (std::ostream & os, const Point & rhs);
private:
	double _ix;
	double _iy;
};
std::ostream & operator << (std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}
int main(void)
{
	Point pt1(2.2,3.3);
	cout <<"pt1->func = " << pt1.func<int>() << endl;
	cout << pt1 << endl;
	return 0;
}
