 ///
 /// @file    testSingleton.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-22 14:26:27
 ///
 
#include "Singleton.h"
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
		cout << "Point()" << endl;
	}
	~Point()
	{
		cout <<"~Point()" << endl;
	}
	void print()const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}
private:
	int _ix;
	int _iy;
};
int main(void)
{
	Point * pt1 = Singleton<Point>::getInstance(1,2);
	Point * pt2 = Singleton<Point>::getInstance(1,2);
	pt1->print();
	pt2->print();
	cout << "pt1 = " << pt1 << endl;
	cout << "pt2 = " << pt2 << endl;
	return 0;
}
