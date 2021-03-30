#ifndef __COMPUTER_H__
#define __COMPUTET_H__

#include<iostream>
using std::endl;
using std::cout;

class Computer
{
public:
	Computer(const char * brand, float price);
	//void setBrand(const char * brand);
	//void setPrice(float price);
	Computer(const Computer & rhs);
	void print();
	void setBrand(const char * brand);
	~Computer();
private://封装，在类之外不能直接访问的
	char * _brand;//品牌// brand_ m_brand成员变量的三种写法
	float _price;//价格
};


#endif
