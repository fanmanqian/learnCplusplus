 ///
 /// @file    Line.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-08 10:32:25
 ///
#include "Line.h" 
#include <iostream>
using std::cout;
using std::endl;
 

class Line::LineImpl
{
public:
	//嵌套类 、类中类
class Point
{
public:
	Point()
	: _ix(0)
	, _iy(0)
	{
		cout << "Point()" << endl;
	}

	Point(int ix, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	void printPoint() const
	{
		cout << "(" << _ix << "," << _iy << ")";
	}

	~Point()
	{
		cout << "~Point()" << endl;
	}

private:
	int _ix;
	int _iy;
};
public:
	Line(int x1,int y1,int x2,int y2)
	: _pt1(x1,y1)
	, _pt2(x2,y2)
	{
		cout << "Line(int,int,int,int)" << endl;
	}

	void printLine()const
	{
		_pt1.printPoint();
		cout << "--->";
		_pt2.printPoint();
		cout << endl;
	}
private:
	Point _pt1;
	Point _pt2;
};

Line::Line(int x1,int y1,int x2,int y2)
: _pimpl(new LineImpl(x1,y1,x2,y2))
{
	cout << "Line(int,int,int,int)" << endl;
}


Line::~Line()
{
	delete _pimpl;
	cout << "~Line()" << endl;
}


void Line::printLine() const
{
	_pimpl->printLine();

}
int main(void)
{
	Line line(1,2,3,4);
	line.printLine();
	Line::Point pt(1,2);
	pt.printPoint();
	return 0;
}
