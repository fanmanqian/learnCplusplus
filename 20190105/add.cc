#include<stdio.h> //C++都要用C的方式去调用C的库（为了兼容C的程序，不对C的程序进行名字改编），对C的库不能采用名字改编的技术 所以printf名字没变Main函数是
				//入口地址也不能采用名字改编
#include<iostream>
using std::cout;
using std::endl;
//用C的方式调用: 不进行名字改编
//
//用C++的方式调用: 进行名字改编

//C++支持函数重载(overload)
//实现原理: 名字改编
//具体的操作步骤: 当函数名称相同时，根据参数的类型、个数、顺序进行改编 
//代码风格: 一定要注意缩进

int add(int x, int y)
{
	return x + y;
}
int add(int x,int y,int z)
{
	return x + y + z;
}

double add(double x, double y)
{
	return x + y;
}

double add(double x, int y)
{
	return x + y;
}

double add(int x,double y)
{
	return x + y;
}

int main()
{
	int a=3,b=4,c=5;
	cout<<"add(a,b) = "<<add(a,b)<<endl;
	cout<<"add(a,b,c) = "<<add(a,b,c)<<endl;

	return 0;
}
