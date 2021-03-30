 ///
 /// @file    functionTemplate.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 10:06:05
 ///

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
 
template<class T>
T add(T x, T y)
{
	return x + y;
}
//模板特化
template<>
const char * add<const char *>(const char * pc1,const char * pc2)
{
	size_t len = strlen(pc1) + strlen(pc2) + 1;
	char * ptmp = new char[len]();
	strcpy(ptmp,pc1);
	strcat(ptmp,pc2);
	return ptmp;
}

int main(void)
{
	int a = 3, b = 4;
	double da = 3.4, db = 4.3;
	char ca = 'a',cb = 1;
	const char * p1 = "hello";
	const char * p2 = "world";
	cout << "a + b = " << add(a, b) << endl;
	cout << "da + db = " << add(da,db) << endl;
	cout << "ca + cb = " << add(ca,cb) << endl;
	cout << "p1 + p2 = " << add(p1,p2) << endl;
	return 0;
}
