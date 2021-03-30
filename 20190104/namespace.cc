#include<iostream>
//using namespace std;//using 编译指令，一次性把std空间中的所有实体引用到程序中来,如果我们定义了该空间中有的实体比如cout那么将会出现错误
//using std::cout;//using 声明机制 引入std空间中的一个实体cout 推荐使用
namespace wd
{
//在其内部定义通称为实体
	int number = 10;
	void display()
	{
		cout<<"wd::display()"<<endl;
	}
}//end of namespace wd

int cout()
{
	cout<<"hello"<<endl;
}
int main()
{

	cout<<"number= "<< wd::number<<endl;//作用域限定符
	wd::display();
	return 0;
}
