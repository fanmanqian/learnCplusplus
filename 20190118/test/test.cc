 ///
 /// @file    test.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 10:12:29
 ///
#include "add.h" 
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	int ia = 1, ib = 2;
	double da = 3.3, db = 4.4;
	cout << "ia + ib = " << add(ia,ib) << endl;
	cout << "da + db = " << add(da,db) << endl;
	return 0;
}
