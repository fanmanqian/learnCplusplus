#include<iostream>
using std::cout;
using std::endl;

class Point
{
public:
	//当类中没有显示定义构造函数时，编译器会自动提供一个默认（无参）的构造函数
	//构造函数的作用就是用来初始化数据成员的
	//构造函数支持函数重载
	Point()
	: _ix(0)//这才是真正的初始化，初始化列表(表达式)
	, _iy(0)
	{
		cout << "Point()" << endl;
		//_ix = 0;
		//_iy = 0;
	}
	//显示定义的构造函数之后，系统就不会再自动提供默认构造函数
	//此时如果还希望能够调用默认构造函数，就必须显示提供一个
	Point(int ix, int iy)
	: _ix(ix)
	, _iy(iy)
	{
		//_ix = ix;
		//_iy = iy;
		cout << "Point(int, int)" << endl;
	}
	//析构函数只有一个，即使不写，系统也会自动提供一个析构函数
	//无参的
	//
	~Point()
	{
		//析构函数的作用是执行清理操作
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

int main()
{
	Point p1(3,4);//栈区 当栈对象被销毁的时候会自动调用析构函数
	p1.print();
	return 0;
}
