 ///
 /// @file    scope.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-08 10:06:45
 ///
 
#include <iostream>
using std::cout;
using std::endl;

int x = 1;
namespace wd
{
int x = 10;
class Example
{
public:
	Example(int data)
	: x(data)
	{ }
	void print(int x) const
	{
		cout << "x = " << x << endl;
		cout << "数据成员x = " << this->x << endl;
		cout << "数据程艳x = " << Example::x << endl;
		cout << "命名空间wd中的x = " << wd::x << endl;
		cout << "全局的x = " << ::x << endl;
	}
private:
	int x;
};
}
int main(void)
{
	wd::Example e(11);
	e.print(4);
	return 0;
}
