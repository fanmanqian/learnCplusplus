 ///
 /// @file    test.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-17 09:59:02
 ///

#include "Singleton.h"
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	Singleton * pt1 = Singleton::getInstance();
	Singleton * pt2 = Singleton::getInstance();
	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;
	Singleton::destroy();
	return 0;
}
