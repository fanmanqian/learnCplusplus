#include<iostream>
using std::cout;
using std::endl;
//C++/Java/C 编译型(静态)语言
//动态语言 没有太好的调试工具 解释执行 没有编译的过程
//宏定义发生的时机是预处理，只会简单的进行字符串替换，没有类型检查;在运行时出现了bug
//不利于错误的发现
#define Max 1024
//#define multi(x,y) x*y //仅仅是进行字符串的替换 1+2*3+4 = 11 出错
//避免这种错误的发生就是加上小括号
#define multi(x,y) (x)*(y)

//C++更多的一种定义常量的方式
//
//发生的时机是编译时，有类型检查，如果出现问题，在编译时就会报错
int const kMax=1024;
const int kMin=1;
int multiply(int x)
{
	return x * Max;
}
int add(int x,int y)
{
	return x+y+kMin+kMax;
}
int main()
{
	cout<<multiply(10)<<endl;
	cout<<add(3,4)<<endl;
	cout<<multi(1+2,3+4)<<endl;
	return 0;
}
