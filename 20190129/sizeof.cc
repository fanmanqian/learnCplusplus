 ///
 /// @file    sizeof.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-26 13:24:26
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Example
{
public:
	Example(int & ref)
	: _ref(ref)
	{

	}
	
	virtual//虚函数指针占8字节
	void display() const
	{
		cout << "Example::display" << endl;
	}
private:
	int ib;//int 型占用4个字节
	char cb;//char占用一个字节 1
	short _sc[5];//一个short占两个字节 现在有5个 所以占10个字节
	static float fb;//由于是静态所以是存放到全局静态区 不占用类自身的空间
	double db;//占8字节
	int & _ref;//相当于指针 如果是64位系统占8字节  如果是32位系统占4字节
};
//在计算整个的时候要考虑系统位数要考虑对齐 64位系统默认8字节对齐 32位系统默认4字节对齐
//# progma pack(2) 出现这个表示的就是按2个字节对齐

int main(void)
{
	cout << "sizeof(Example)" << sizeof(Example) << endl;
	return 0;
}
