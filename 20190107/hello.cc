#include<stdio.h>
#include<iostream>
using std::endl;
using std::cout;

int a=1;//全局变量默认情况下自动初始化为0
char * p1;
int main()
{
	int b=2;
	static int c=3;
	char s[]="123456";
	char *p2;
	char * p3 = "1234";
	printf("&a= %p\n",&a);
	printf("&b= %p\n",&b);
	printf("&s= %p\n",&s);
	printf("&p1= %p\n",&p1);
	printf("&p2= %p\n",&p2);
	printf("&p3= %p\n",&p3);
	printf("&c= %p\n",&c);

	return 0;
}
