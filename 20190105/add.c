#include<stdio.h>
//C语言并不支持函数重载
int add(int x,int y)
{
	return x + y;
}
int add(int x,int y,int z)
{
	return x + y + z;
}

int main()
{
	int a=3,b=4,c=5;
	printf("add(a,b) = %d\n",add(a,b));
	printf("add(a,b,c) = %d\n",add(a,b,c));
	return 0;
}
