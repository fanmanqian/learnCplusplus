 ///
 /// @file    forbidcopy.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-25 11:18:50
 ///
 
#include <iostream>
using std::cout;
using std::endl;


//值传递 ----> 值语义 ------> 能够进行复制
//对象语义 ----> 不能进行复制

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int) " << endl;
	}

	void print() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}
	//禁止复制
	//C++11的用法
	Point(const Point & rhs) = delete;
	Point & operator= (const Point & rhs) = delete;

private://C++11之前
	//Point(const Point & rhs);
	//Point & operator= (const Point & rhs);

private:
	int _ix;
	int _iy;
};


int main(void)
{
	Point pt1(1, 2);
	Point pt2(pt1);//error 
	Point pt3(3, 4);
	pt3 = pt1;//error
}
