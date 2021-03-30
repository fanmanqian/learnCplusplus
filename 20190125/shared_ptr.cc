 ///
 /// @file    shared_ptr.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 12:00:46
 ///
 
#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::shared_ptr;
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
	shared_ptr<int> up(new int(3));
	cout << "*up = " << *up << endl;
	cout << "up = " << up.get() << endl;
	cout << "up's use_count = " << up.use_count() << endl;

	shared_ptr<int> up3(up);//共享所有权的指针 进行复制或赋值时将引用计数加1 当up3被销毁时 引用计数减一 就是如果是放在语句块里面 出语句块的时候 会被销毁
	cout << "*up = " << *up << endl;
	cout << "up = " << up.get() << endl;
	cout << "up's use_count = " << up.use_count() << endl;
	cout << "*up3 = " << *up3 << endl;
	cout << "up3 = " << up3.get() << endl;
	cout << "up3's use_count = " << up3.use_count() << endl;
	
	shared_ptr<int> up4(new int(4));
	up4 = up3;
	cout << "*up = " << *up << endl;
	cout << "up = " << up.get() << endl;
	cout << "up's use_count = " << up.use_count() << endl;
	cout << "*up3 = " << *up3 << endl;
	cout << "up3 = " << up3.get() << endl;
	cout << "up3's use_count = " << up3.use_count() << endl;
	cout << "*up4 = " << *up4 << endl;
	cout << "up4 = " << up4.get() << endl;
	cout << "up4's use_count = " << up4.use_count() << endl;

	cout << "移动" << endl;
	shared_ptr<int> up1(std::move(up));//有移动构造函数 通过移动构造函数进行所有权的转移
	cout << "*up1 = " << *up1 << endl;
	cout << "up1 = " << up1.get() << endl;
	cout << "up1's use_count = " << up1.use_count() << endl;
	cout << "*up = " << *up3 << endl;
	cout << "up = " << up3.get() << endl;
	cout << "up's use_count = " << up3.use_count() << endl;

	//他有移动构造函数所以可以纳入vector容器中
	vector<shared_ptr<int>> numbers;
	numbers.push_back(std::move(up1));
	numbers.push_back(up4);//也可以 因为有复制构造
	
	shared_ptr<Point> up5(new Point(3,4));
	vector<shared_ptr<Point>> pPoints;
	pPoints.push_back(shared_ptr<Point>(new Point(1,2)));
	pPoints.push_back(up5);//也可以 因为有复制构造
	return 0;
}
