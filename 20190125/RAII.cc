 ///
 /// @file    RAII.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 11:07:35
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
template<class T>
class RAII
{
public:
	RAII(T * data)
	: _data(data)
	{}
	
	T * operator->()
	{
		return _data;
	}

	T & operator*()
	{
		return *_data;
	}

	//改变指针指向 托管其他对象
	void reset(T * data)
	{
		if(_data) {
			delete _data;
		}
		_data = data;
	}

	~RAII()
	{
		if(_data)
			delete _data;
	}
private:
	T * _data;
};

class Point
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

	~Point()
	{ cout << "~Point()" << endl; } 
private:
	int _ix;
	int _iy;
};
int main(void)
{
	RAII<Point> pPoint(new Point(1,2));
	pPoint->display();
	(*pPoint).display();
	pPoint.reset(new Point(3,4));
	pPoint->display();
	return 0;
}
