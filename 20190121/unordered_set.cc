 ///
 /// @file    unordered_multiset.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-04 11:20:17
 ///
 
#include <iostream>
#include <unordered_set>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::unordered_multiset;

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
bool operator==(const Point & lhs,const Point & rhs)
{
	return (lhs.getX()==rhs.getX()) && (lhs.getY()==rhs.getY());
}
//2.hash重写或者在第二个参数列表加入PointHash
namespace std
{
template<>
struct hash<Point>
{
	size_t operator()(const Point & pt) const
	{
		return (pt.getX() << 1 ) ^ (pt.getY() << 1);
	}
};
}
//PointHash
struct PointHash
{
	size_t operator()(const Point & pt) const
	{
		return (pt.getX() << 1 ) ^ (pt.getY() << 1);
	}

};

void test0()
{
	unordered_multiset<int> numbers{8,9,12,3,4,1,2};
	for(auto & elem : numbers){
		cout << elem << " ";
	}
	cout << endl;
}

void test1()
{
	vector<Point> points = {Point(1,2),Point(3,4),Point(5,6)};
	//unordered_multiset<Point> points_set(points.begin(),points.end());
	unordered_multiset<Point,PointHash> points_set(points.begin(),points.end());
	auto ret = points_set.insert(Point(1,2));

	for(auto & elem :points_set){
		cout << elem << " ";
	}
	cout << endl;
}
int main(void)
{
	//test0();
	test1();
	return 0;
}
