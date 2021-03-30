#include<iostream>
using std::cout;
using std::endl;
//引用与指针的异同？
//
void test0()
{
	int number = 10;
	int & ref = number;//引用是一个变量的别名,对引用进行初始化,他的出现就是为了减少指针的使用
	//引用的底层实现就是指针 指针常量
//	int & ref2;//引用必须要进行初始化，它需要绑定到一个实体之上，本身不能独立存在
	          //一经绑定之后，不会再改变指向
	cout<<"修改之前: "<<endl;
	cout<<"number= "<<number<<endl;
	cout<<"ref= "<<ref<<endl;
	ref=100;//操作ref与操作number一样的
	cout<<"修改之后: "<<endl;
	cout<<"number= "<<number<<endl;
	cout<<"ref= "<<ref<<endl;
	cout<<"&number= "<<&number<<endl;
	cout<<"&ref= "<<&ref<<endl;
}
//1.引用作为函数的参数
//副本 copy
//值传递 ==> 进行复制
//void swap(int x,int y)
//{
//	int temp = x;
//	x = y;
//	y = temp;
//
//}
//地址传递 ==> 值传递
//void swap(int * px,int * py)
//{
//	int temp = *px;//解引用 -> 间接访问
//	*px = *py;
//	*py = temp;
//
//}
//引用作为形参,操作引用的时候,就跟操作实参是一样的
//引用传递
// 优势:不需要为参数开辟额外的空间，不需要进行复制，
//      提高程序执行效率
void swap(int & x,int & y)
{
	int temp = x;
	x = y;
	y = temp;
}

int func()
{
	int number=10;
	return number;//执行return就会进行复制
}
//2.引用作为函数的返回值,执行return语句时不会进行复制，直接返回实体本身
// 前提条件: 返回的实体的生命周期一定要大于函数
int array[10]={1,2,3,4,5};
int & getIndex(int idx)
{
	return array[idx];
}
int * func2()
{
	int number=100;//这种用法也是错误的
	return &number;
}
//不要返回局部变量的引用
int & getNumber()
{
	int number=0;//局部变量 只存在于函数的栈空间
	return number;//当函数执行完毕后，栈空间会被销毁，局部变量也被销毁
	             //既然已经被销毁，再去操作它就没有意义了
}
//既然栈空间的局部变量无法操作 我们是不是就可以操作堆空间的变量
//不要轻易去返回一个堆空间的引用，这样做有可能发生内存泄漏
//除非有了一个内存回收的策略
int & getHeapVariable()
{
	int * pNumber = new int(10);
	return *pNumber;
}

void test2()
{
	cout<<"getIndex(0) = "<< getIndex(0) <<endl;
	getIndex(0)=10;
	cout<<"getIndex(0) = "<< getIndex(0) <<endl;
	cout<<"array[0] = "<< array[0] <<endl;
}
void test3()
{
	int a = 1, b = 2;
	int c = a + getHeapVariable() + b;
	cout<<"c= "<<c<<endl;
	//92-94造成了内存泄漏
	int & ref = getHeapVariable();
	cout<<ref<<endl;
	delete &ref;
}
int main()
{
	//test0();
//	int a = 3,b = 4;
//	cout<<"交换之前的:"<<endl;
//	cout<<a<<" "<<b<<endl;
	//swap(a,b);int & x = a;int & y = b 引用的使用更加顺其自然
	//swap(&a,&b);指针的使用不够直观
	//swap(a,b);
	//cout<<"交换之前的:"<<endl;
	//cout<<a<<" "<<b<<endl;	
	test3();
	return 0;
}
