#ifndef __COMPUTER_H__
#define __COMPUTET_H__

class Computer
{
public:
	void setBrand(const char * brand);
	void setPrice(float price);
	void print();
private://封装，在类之外不能直接访问的
	char _brand[20];//品牌// brand_ m_brand成员变量的三种写法
	float _price;//价格
};

#endif
