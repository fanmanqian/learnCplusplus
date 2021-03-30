#include<stdio.h>//C的头文件在C++头文件的前面 如果还有自定义头文件 要放在最前面
#include<string.h>

#include<iostream>
#include<string>

using std::cout;
using std::endl;
//C语言字符串拼接
void test0()
{
	char str1[] = "hello";//字符串是以'\0'结尾 栈区
	char str2[] = "world";//严格来说是一个字符数组
	//str1 = 0x0001;//数组名本身就是一个常量 不能被修改
	int len1 = sizeof(str1);
	int len2 = sizeof(str2);
	printf("str1's len = %d, str2's len = %d\n",len1,len2);
	//字符串拼接
	int len = len1 + len2 - 1;
	char * pstr1 = (char*)malloc(len);
	memset(pstr1,0,len);
	strcpy(pstr1,str1);
	strcat(pstr1,str2);
	printf("pstr1's : %s\n",pstr1);
	free(pstr1);
	//C风格的字符串
	const char * pstr2 = "hello.world";//指针定义字符串 位于文字常量区 
	//*pstr2 = 'H';//error
}
//C++字符串拼接
void test1()
{
	//C++风格的字符串
	std::string s1 = "hello";//const char * C风格字符串转换成C++风格的字符串
	std::string s2 = "world";
	//也可以像字符数组一样用下标去访问
	cout<<"s2[0] = " << s2[0] << endl;
	std::string s3 = s1 + s2;
	cout<<"s1 = "<<s1 << ",s2= "<<s2<<endl;
	cout<<"s3 = "<<s3<<endl;
	//把C++风格字符串转换成C风格字符串
	const char * p1 = s3.c_str();
	cout << "p1 = " << p1 << endl;
	//获取字符串长度
	size_t len = s1.size();
	size_t len2 = s1.length();
	cout<<len<<" "<<len2<<endl;
	//遍历内容
	for(size_t idx = 0; idx != s3.size();++idx)
	{
		cout<<s3[idx]<<endl;
	}
	//其他拼接方式
	std::string s4 = s3 + "shenzhen";
	cout<<s4<<endl;
	std::string s5 = s4 + 'A';
	s5.append(s1);
	cout<<s5<<endl;
	//子符串截取子串
	size_t pos = s5.find("shenzhen");

	std::string s6 = s5.substr(pos,10);
	cout<<"s6 = "<<s6<<endl;
}

int main()
{
	test0();
	test1();
	return 0;
}

