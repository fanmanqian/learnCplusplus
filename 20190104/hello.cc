#include<stdio.h>
#include<iostream> //C++头文件都是用模板编写的，而模板的特点:必须要知道所有的实现才能正常编译
using namespace std;//命名空间

int func(int);//函数声明 可以多次声明
int func(int);//函数声明
int func(int);//函数声明

//printf(const char * format,...);第二个参数代表的是可变参数

//函数的定义 只能有一次
int test()
{
	printf("hello,world\n");//标准库函数
	cout<<"hello,world"<<endl;//cout 代表的是一个对象 ，标准输出
							//endl表示的是换行
							//stdout	
	int number=0;
	cin>>number;//cin对象，代表的是标准输入 >> 输入流运算符
	return 0;
}

int main(int argc,char ** argv)
{
	test();
	return 0;
}
