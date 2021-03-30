#include<iostream>
using std::endl;
using std::cout;
//默认参数/缺省参数的设置必须是从右到左进行 设置默认参数时候注意二义性
int add(int x, int y, int z = 0)//这里的z就是默认参数
{
	return x + y + z;
}
//当传递两个参数的时候到底是调用5-8还是10-13这里就产生了二义性
int add(int x,int y)
{
	return x + y;
}
int main()
{
	int a=3,b=4,c=5;
	cout<<"add(a,b,c) = "<< add(a,b,c)<<endl;
	cout<<"add(a,b) = "<<add(a,b)<<endl;//调用的时候又叫缺省参数
	return 0;
}



