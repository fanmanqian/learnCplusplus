#include<iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int, int)" << endl;
	}
	//编译器提供的copy constructor 这里可以省略不写 用系统自动提供的 
	Point(const Point & rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout << "Point(const Point &)" << endl;
	}
	~Point()
	{
		cout<< "~Point()" << endl;
	}

	void print()
	{
		cout << "(" <<_ix
			 << ", "<< _iy
			 << ")" << endl;
	}
private:
	int _ix;
	int _iy;
};

void test()
{
	Point pt1(3,4);
	pt1.print();
	cout << endl;
	Point pt2 = pt1;//调用复制(拷贝)构造函数,copy constructor
	cout << endl;
	pt2.print();
}
int main()
{
	test();
	return 0;
}
