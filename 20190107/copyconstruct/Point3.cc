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
	//赋值运算符函数的原型
	//如果返回值为对象，在执行return 语句时，会调用复制构造函数的
	//增加程序的开销，所以返回值还是要加引用，
	//如果返回值是void型 那就无法实现连等=
	Point & operator=(const Point & rhs)
	{
		_ix = rhs._ix;
		_iy = rhs._iy;
		return *this;
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
//复制构造函数的调用时机2,当采用值传递时,形参与实参都是对象,进行形参与实参结合时
void func(Point pt)
{
	pt.print();
}
void test1()
{
	Point point(1,2);
	func(point);
}

Point func1()
{
	Point point(1,2);//Point(int,int)
	point.print();
	return point;//Point(const Point&)
}

void test2()
{
	Point pt = func1();//Point(const Point&)
	pt.print();
}
void test3()
{
	//int a = 3, b = 4, c =5;
	//a = (b = c);//内置类型

	Point pt1(1, 2);
	cout << "pt1 = ";
	pt1.print();

	Point pt2(11, 22);
	cout << "pt2 = ";
	pt2.print();

	pt1 = pt2; // 将赋值操作移植到Point类型上，调用的 赋值运算符函数
	           // 赋值运算符的左右操作数都是存在的，不需要构造
	//等价于
	pt1.operator=(pt2);
	cout << "pt1 = ";
	pt1.print();
}
int main()
{
	test3();
	return 0;
}
