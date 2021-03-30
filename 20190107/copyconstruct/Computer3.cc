#include "Computer.h"
#include<stdio.h>
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
//系统提供的复制构造函数 不能满足我们的需求 此时我们需要自己定义复制构造函数
//Computer::Computer(const Computer & rhs)
//:_brand(rhs._brand)//隐藏的bug 浅拷贝 直接复制指针值
//,_price(rhs._price)
//{
//	cout << "Computer(const Computer &)" << endl;
//}
//自定义复制构造函数
Computer::Computer(const Computer & rhs)
:_brand(new char[strlen(rhs._brand) + 1]())
,_price(rhs._price)
{
	strcpy(_brand,rhs._brand);//先开空间 再复制内容 深拷贝
	cout << "Computer(const Computer &)" << endl;
}
void Computer::print()
{
	printf("_brand=%p\n",_brand);

	cout<<"brand: "<<_brand<<endl;
		
	cout<<"price: "<<_price<<endl;
}

void Computer::setBrand(const char * brand)
{
	size_t len = strlen(_brand);
	if(len > strlen(brand)){
		strcpy(_brand,brand);
	}
	else{
		delete [] _brand;
		_brand  = new char[strlen(brand) + 1]();
		strcpy(_brand,brand);
	}
}

Computer::~Computer()
{
	delete [] _brand;
	cout << "~Computer" << endl;
}

