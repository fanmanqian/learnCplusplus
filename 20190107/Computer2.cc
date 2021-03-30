#include<string.h>
#include<iostream>
using std::cout;
using std::endl;

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

void Computer::setBrand(const char * brand)
{
	strcpy(_brand,brand);
}
void Computer::setPrice(float price)
{
	_price=price;
}
void Computer::print()
{
	cout<<"brand: "<<_brand<<endl;
		
	cout<<"price: "<<_price<<endl;
}
int main()
{
	Computer c1;
	c1.setBrand("le");
	c1.setPrice(5555);
	c1.print();
	//c1._price=7777;//错误的因为类外不能访问私有成员
	return 0;
}
