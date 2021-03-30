 ///
 /// @file    VaridicTemplates.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 10:57:43
 ///
 
#include <iostream>
using std::cout;
using std::endl;
template<typename...Args>//Args模板参数包
void print(Args... args)//args函数参数包
{
	cout << "sizeof...(Args) = " << sizeof...(Args) << endl;
	cout << "sizeof...(args) = " << sizeof...(args) << endl;
	//cout << (args...) << endl;
}
//display递归条件的出口
void display()
{
	cout << endl;
}
template<class T, class... Args>
void display(T t, Args... args)//函数参数包声明时，在其左边
{
	cout << t << " ";
	display(args...);//当...在函数参数包右边时，表示展开参数包
}
//累加的递归出口
template<class T>
T sum(T t)
{
	return t;
}
template<class T,class... Args>
T sum(T t,Args... args) 
{
	return t + sum(args...);
}

int main(void)
{
	print(1);
	print(1,1.1);
	print(1,1.1,'c');
	display(1);
	display(1,1.1);
	display(1,1.1,'c');
	cout << "sum(1,2,3,4,5,6,7) = " << sum(1,2,3,4,5,6,7) << endl;
	return 0;
}
