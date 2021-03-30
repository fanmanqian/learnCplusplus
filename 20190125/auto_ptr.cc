 ///
 /// @file    auto_ptr.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 11:58:26
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::auto_ptr;
 
int main(void)
{
	int * pt = new int(3);
	cout << "pt = " << pt << endl;
	auto_ptr<int> ap(pt);
	cout << "*ap = " << *ap << endl;
	cout << "ap = " << ap.get() << endl;
	auto_ptr<int> ap1(ap);//复制构造函数 在语法形式上是复制操作 但底层已经发生了所有权的转移
						  //该智能指针存在缺陷
	cout << "*ap1 = " << *ap1 << endl;
	cout << "*ap = " << *ap << endl;
	return 0;
}
