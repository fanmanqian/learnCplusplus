#include<iostream>
using std::cout;
using std::endl;
//没有函数的开销，提高程序的执行效率
#define multiply(x,y) ((x)*(y))

//函数调用有开销的 因为要保存现场和恢复现场  就是具体来说先用栈存下该函数的内容 用完以后销毁栈
//inline函数的效果与带参数的宏定义是一样的
//同时又可以进行编译，安全性比带参数的宏定义高的多

//编译器优化: 现代编译器自动识别一个函数是否可以设置为inline函数
inline
int divide(int x, int y)
{
	return x / y;
}
int main()
{
	int a = 3, b = 4;
	cout << multiply(a,b) << endl;
	return 0;
}
