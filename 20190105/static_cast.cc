#include<iostream>
using std::cout;
using std::endl;
int test0()
{
	int number1 = 10;
	double number2 = 11.11;
	//C的强制转换的两种方式
	//number1 = (int)number2;
	number1 = int(number2);
	cout<<"number1 = "<<number1<<endl;
	return 0;
}

void test1()
{
	int number1 = 10;
	double number2 = 11.11;
	//C++的一种初始化变量的方式
	int number3(12);
	cout<<"number3 = "<<number3<<endl;
	//C++强制类型转换 方便查找在哪些地方发生了强制类型转换
	number1 = static_cast<int>(number2);
	cout<<"number1 = "<<number1<<endl;
	//malloc本身的返回值是void* 然后需要初始化才能赋值 现在
	//使用强制转换将其变成int* 就不再需要初始化了
	int * pInt = static_cast<int*>(malloc(sizeof(int)));
	*pInt = 10;
	cout<<"*pInt = "<<*pInt<<endl;
	free(pInt);
	//const_cast/dynamic_cast/reinterpret_cast 用法类似
//	return 0;
}
int main()
{

	test1();
	return 0;
}
