 ///
 /// @file    unordered_multiset.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-04 11:20:17
 ///
 
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using std::vector;
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::make_pair;

template<class Container>
void display(const Container & c)
{
	for(auto & elem : c)
	{
		cout << elem.first << "---->" << elem.second << endl;
	}
	//cout << endl;
}

void test0()
{
	unordered_map<string,string> cities{
		make_pair("111","日本"),
		make_pair("222","中国"),
		//make_pair("111","武汉"),
		make_pair("333","天津")
	};
	display(cities);
}

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
void test1()
{
	vector<Point> points = {Point(1,2),Point(3,4),Point(5,6)};
	//unordered_multiset<Point> points_set(points.begin(),points.end());
	unordered_map<string,Point> points_map{
		make_pair("111",Point(1,2)),
		make_pair("222",Point(3,4)),
		make_pair("333",Point(5,6))
	};
	display(points_map);
	cout << "插入后" << endl;
	auto ret = points_map.insert(make_pair("444",Point(7,8)));
	display(points_map);
	cout << "points_map[222]=" << points_map["222"] << endl;
	points_map["222"] = Point(-1,-10);
	display(points_map);
}
int main(void)
{
	//test0();
	test1();
	return 0;
}
