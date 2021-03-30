#include "Computer.h"
#include<string.h>
#include<iostream>
using std::cout;
using std::endl;
Computer::Computer(const char * brand, float price)
: _brand(new char[strlen(brand) + 1]())
, _price(price)
{
	//用sizeof是计算的一个指针的大小而不是长度要用strlen
	cout << "sizeof(brand) " << sizeof(brand) << endl;
	strcpy(_brand,brand);
	cout << "Computer(const char *, float)" << endl;
}
void Computer::print()
{
	cout<<"brand: "<<_brand<<endl;
		
	cout<<"price: "<<_price<<endl;
}
Computer::~Computer()
{
	delete [] _brand;
	cout << "~Computer" << endl;
}

