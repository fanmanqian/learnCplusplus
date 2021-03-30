#include<stdlib.h>
#include<string.h>
#include<iostream>
using std::cout;
using std::endl;
void test0()
{
	int* pINT=(int*)malloc(sizeof(int));//开辟动态空间 堆空间
	//开辟空间以后要初始化
	memset(pINT,0,sizeof(int));//空间清理
	*pINT=10;//赋值
	cout<<"*pINT的值: "<<*pINT<<endl;//打印
	free(pINT);//释放空间
}
//test1说明了堆空间的数据其生命周期是大于函数的 C语言
int* test1()
{
	int* pINT=(int*)malloc(sizeof(int));//开辟动态空间 堆空间
	//开辟空间以后要初始化
	memset(pINT,0,sizeof(int));//空间清理
	*pINT=10;//赋值
	cout<<"*pINT的值: "<<*pINT<<endl;//打印
	cout<<"pINT的值: "<<pINT<<endl;//打印
	cout<<"&PINT: "<<&pINT<<endl;
	//free(pINT);//释放空间
	//C语言开辟数组的方式
	int* pArray = (int*)malloc(sizeof(int)*10);
	memset(pINT,0,sizeof(int)*10);

	return pINT;
}
//new/delete表达式的使用 C++
void test2()
{
	int* pINT=new int(10);
	cout<<"*pINT的值: "<< *pINT<<endl;
	cout<<"pINT的值: "<<pINT<<endl;//pINT所指空间
	cout<<"&pINT: "<<&pINT<<endl;//pINT本身所在的空间
	delete pINT;
	//开辟数组的方式 40-42
	int* pArray = new int[10]();
	pArray[0]=1;
	delete [] pINT;
}
int main()
{
//	int* p1 = test1();
//	cout<<"*p1的值: "<<*p1<<endl;
//	cout<<"p1的值: "<<p1<<endl;
//	cout<<"p1的地址值: "<<&p1<<endl;
//	free(p1);
	test2();

	return 0;
}
