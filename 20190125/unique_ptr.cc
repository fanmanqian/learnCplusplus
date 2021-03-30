 ///
 /// @file    unique_ptr.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 12:00:46
 ///
 
#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

class Point
{
public:
	Point(int ix,int iy)
	: _ix(ix)
	, _iy(iy)
	{ cout << "Point(int,int)" << endl; }

	void display() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	~Point()
	{ cout << "~Point()" << endl; } 
private:
	int _ix;
	int _iy;
};

int main(void)
{
	unique_ptr<int> up(new int(3));
	cout << "*up = " << *up << endl;
	cout << "up = " << up.get() << endl;

//	unique_ptr<int> up3(up);//独享所有权的指针  没有复制构造函数
//	unique_ptr<int> up4(new int(4));
//	up3 = up4;//独享所有权的指针 没有赋值运算符函数 不能进行赋值
	unique_ptr<int> up1(std::move(up));//有移动构造函数 通过移动构造函数进行所有权的转移
	cout << "*up1 = " << *up1 << endl;
	cout << "up1 = " << up1.get() << endl;
	//他有移动构造函数所以可以纳入vector容器中
	vector<unique_ptr<int>> numbers;
	numbers.push_back(std::move(up1));
	
	vector<unique_ptr<Point>> pPoints;
	pPoints.push_back(unique_ptr<Point>(new Point(1,2)));
	return 0;
}
