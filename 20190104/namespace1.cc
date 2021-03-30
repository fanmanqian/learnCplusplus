#include<iostream>
using std::cout;
using std::endl;
//带命名空间的函数声明

namespace ds
{
	void print();
}
namespace wd
{
//在其内部定义通称为实体
	int number = 10;
	void display()
	{
		cout<<"wd::display()"<<endl;
	}
	ds::print();
}//end of namespace wd

namespace ds
{
	int number=20;
	void show()
	{
		cout<<"ds::show()"<<endl;
	}
	void print()
	{
		cout<<"ds::print()"<<endl;
		wd::display();
	}
}
int main()
{
	return 0;
}
