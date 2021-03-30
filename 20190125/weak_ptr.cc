 ///
 /// @file    weak_ptr.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 13:56:31
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::weak_ptr;
using std::shared_ptr;

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
	weak_ptr<Point> wp;
	{
		shared_ptr<Point> sp(new Point(1,2));
		wp = sp;
		cout << "sp's use_count = " << sp.use_count() << endl;
		cout << "wp's use_count = " << wp.use_count() << endl;
		cout << "wp is expired = " << wp.expired() << endl;
		shared_ptr<Point> sp1 = wp.lock();
		if(sp1) {
			cout << "提升成功" << endl;
			cout << "*sp1 ";
			sp1->display();
		} else {
			cout << "提升失败,被托管的对象已经被销毁了." << endl;
		}
	}
	cout << "wp is expired = " << wp.expired() << endl;
	shared_ptr<Point> sp1 = wp.lock();
	if(sp1) {
		cout << "提升成功" << endl;
		cout << "*sp1 ";
		sp1->display();
	} else {
		cout << "提升失败,被托管的对象已经被销毁了." << endl;
	}
	return 0;
}
