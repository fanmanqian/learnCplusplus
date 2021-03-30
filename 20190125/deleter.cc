 ///
 /// @file    deleter.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 15:23:04
 ///
 
#include <iostream>
#include <string>
#include <memory>
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
//使用函数对象完成资源的定制化回收方式
struct FileClose
{
	void operator()(FILE * fp)
	{
		if(fp) {
			fclose(fp);
			cout << "fclose()" << endl;
		}
	}
};

//use unique_ptr在模板中传入删除器
void test0()
{
	unique_ptr<FILE,FileClose> up(fopen("test0.txt","a"));
	string content = "hello,world\n";
	fwrite(content.c_str(),1,content.size(),up.get());
}
//use shared_ptr在构造函数中传入删除器对象
void test1()
{
	shared_ptr<FILE> up(fopen("test0.txt","w"),FileClose());
	string content = "hello,world\n";
	fwrite(content.c_str(),1,content.size(),up.get());
}

int main(void)
{
	test0();
	//test1();
	return 0;
}
