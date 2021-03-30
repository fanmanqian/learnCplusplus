 ///
 /// @file    bind.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-07 15:46:21
 ///
 
#include <iostream>
#include <functional>
using std::bind;
using std::cout;
using std::endl;


class Example
{
public:
	int add(int x, int y)
	{
		return x + y;
	}
};


int add(int x, int y)
{
	return x + y;
}


void test0()
{
	auto f1 = bind(add,1,2);
	cout << "f1() = " << f1() << endl;
	//占位符 
	auto f2 = bind(add,1,std::placeholders::_1);
	cout << "f2(2) = " << f2(2) << endl;
	//自定义类型函数绑定
	Example e1;
	auto f3 = bind(&Example::add,&e1,1,2);
	cout << "f3() = " << f3() << endl;
}

//C语言的函数指针
typedef int(*Function)();

int add1()
{
	return 5;
}

int add2()
{
	return 10;
}
void test1()
{
	Function f1 = add1;//给f1注册回调函数 C语言用函数指针实现多态
	cout << "f1() = " << f1() << endl;//执行回调函数
	f1 = add2;
	cout << "f1() = " << f1() << endl;
}
int main(void)
{
	test0();
	test1();
	return 0;
}
