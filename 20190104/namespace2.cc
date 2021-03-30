#include<iostream>
using std::cout;
using std::endl;
int number=1;
namespace wd
{
	int number=10;
	void display(int number)
	{
		cout<<"number= "<<number<<endl;
		cout<<"wd::number= "<<wd::number<<endl;
		cout<<"全局变量number= "<<::number<<endl;
	}
}
int main()
{
	int value=2;
	wd::display(value);
	return 0;
}
