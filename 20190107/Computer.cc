#include<string.h>
#include<iostream>
using std::cout;
using std::endl;

class Computer
{//大括号里面就称为类的内部
//对于class而言，默认访问权限是private
public://类对外提供的接口，功能，服务
	void setBrand(const char * brand)
	{
		strcpy(_brand,brand);
	}
	void setPrice(float price)
	{
		_price=price;
	}
	void print()
	{
		cout<<"brand: "<<_brand<<endl;
		
		cout<<"price: "<<_price<<endl;
	}
private://封装，在类之外不能直接访问的
	char _brand[20];//品牌// brand_ m_brand成员变量的三种写法
	float _price;//价格
};

int main()
{
	Computer c1;
	c1.setBrand("le");
	c1.setPrice(5555);
	c1.print();
	c1._price=7777;//错误的因为类外不能访问私有成员
	return 0;
}
