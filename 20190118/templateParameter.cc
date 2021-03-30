 ///
 /// @file    templateParameter.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 10:27:43
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
//模板参数可以有两种形式
//1、类型参数
//2、非类型参数，常量表达式，整型bool/char/int/long/short
//
//都可以设置默认值
template<class T = int,short kMin = 10>
T multi(T x, T y)
{
	return x * y * kMin;
}

int main(void)
{
	int a = 4, b = 3;
	cout <<"a * b * kMin = " << multi(a,b) << endl;
	//不使用默认值
	cout <<"a * b * kMin = " << multi<short,5>(a,b) << endl;
	return 0;
}
