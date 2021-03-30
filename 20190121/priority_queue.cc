 ///
 /// @file    priority_queue.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-05 20:16:31
 ///
 
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;


class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{

	}

	int getX() const
	{
		return _ix;
	}
	
	int getY() const
	{
		return _iy;
	}
	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};
std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix << ","
	   << rhs._iy << ")";
	return os;
}
//1.重新定义自定义的==
bool operator>(const Point & lhs,const Point & rhs)
{
	double dist1 = sqrt(lhs.getX()*lhs.getX() + lhs.getY()*lhs.getY());
	double dist2 = sqrt(rhs.getX()*rhs.getX() + rhs.getY()*rhs.getY());
	return dist1 > dist2;
}
void test0()
{
	vector<int> numbers = {3,6,7,8,1,2,9,4,5};
	priority_queue<int> pque;
	for(size_t idx = 0; idx != 9; ++idx)
	{
		pque.push(numbers[idx]);
		cout << "当前优先级最高的元素: " << pque.top() << endl;
	}
	while(!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;
}


void test1()
{
	vector<int> numbers = {3,6,7,8,1,2,9,4,5};
	priority_queue<int,vector<int>,std::greater<int>> pque;
	for(size_t idx = 0; idx != 9; ++idx)
	{
		pque.push(numbers[idx]);
		cout << "当前优先级最高的元素: " << pque.top() << endl;
	}
	while(!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;
}


void test2()
{ 
	vector<Point> points={Point(1,2),Point(3,4),Point(5,6)};
	priority_queue<int,vector<Point>,std::greater<Point>> pque(points.begin(),points.end());
	while(!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;
}
int main(void)
{
	//test0();
	//test1();
	test2();
	return 0;
}
