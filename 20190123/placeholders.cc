 ///
 /// @file    placeholders.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-07 16:52:07
 ///
 
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::bind;

void print(int x1, int x2, int x3, const int & x4,int x5)
{
	cout << x1 << " "
		 << x2 << " "
		 << x3 << " "
		 << x4 << " "
		 << x5 << " ";
}

int main(void)
{
	int number = 100;
	//bind值绑定
    //auto f1 = bind(print,10,std::placeholders::_3,std::placeholders::_4,std::cref(number),number);
	//auto 对应的原型
	std::function<void(int,int,int,int)> f1 = bind(print,10,std::placeholders::_3,std::placeholders::_4,std::cref(number),number);
	number = 1000;
	//_1 _2 表示的是与实参的第几个家伙绑定
	f1(11,12,13,14);
	cout << endl;
	return 0;
}
