#include "Computer.h"
#include<iostream>
using std::cout;
using std::endl;


void test1()
{
	Computer com1("thinkpad",7999);
	cout << "com1: "<< endl;
	com1.print();
	cout << endl;
	Computer com2 = com1;
	cout << "com2: "<< endl;
	com2.print();
	cout << endl;
	//修改com1影响到了com2 无法接受
	com1.setBrand("xiaomi");
	com2.print();
	cout << endl;
}

int main()
{
	test1();
	return 0;
}
