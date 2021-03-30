#include <iostream>
using std::cout;
using std::endl;

class Test
{
public:
	Test(int value)
	: _iy(value)//初始化表达式中数据成员初始化的顺序与在初始化表达式中是顺序无关
	, _ix(_iy)//只与数据成员在被声明时的顺序有关
	{
		cout << "Test(int)" << endl;
	}
	void print()
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}
private:
	int _ix;
	int _iy;
};


int main()
{
	Test t1(1);
	t1.print();
	return 0;
}
