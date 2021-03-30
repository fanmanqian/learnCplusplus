 ///
 /// @file    set.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-17 10:34:10
 ///

#include <math.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
	}
	friend class PointComparator;
	double getDistance() const
	{
		return sqrt(_ix * _ix + _iy * _iy);
	}
	friend bool operator<(const Point & lhs,const Point & rhs);
	friend bool operator>(const Point & lhs,const Point & rhs);
	
	friend std::ostream & operator <<(std::ostream & os,const Point & rhs);
private:
	int _ix;
	int _iy;
};
//函数对象
struct PointComparator
{
	bool operator()(const Point & lhs,const Point & rhs)
	{
		if(lhs.getDistance() < rhs.getDistance()){
			return true;
		}else if(lhs.getDistance()==rhs.getDistance()){
			return lhs._ix < rhs._ix;
		}else{
			return false;
		}
	}
};
bool operator>(const Point & lhs,const Point & rhs)
{
	if(lhs.getDistance() > rhs.getDistance()){
		return true;
	}else if(lhs.getDistance()==rhs.getDistance()){
		return lhs._ix > rhs._ix;
	}else{
		return false;
	}
}
bool operator<(const Point & lhs,const Point & rhs)
{
	if(lhs.getDistance() < rhs.getDistance()){
		return true;
	}else if(lhs.getDistance()==rhs.getDistance()){
		return lhs._ix < rhs._ix;
	}else{
		return false;
	}
}

std::ostream & operator << (std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

	
template<class Container>
void display(const Container & c)
{
	for(auto & elem : c)
	{
		cout << elem << " ";
	}
	cout << endl;
}

void test00()
{
	std::pair<int,string> value(600001,"wanke");
	cout << value.first << "--->" <<value.second << endl;

}
void test0()
{
	//int array[] = {2,1,6,7,2,1,3,4,5,8};
	//set默认按照升序的方式进行排序
	//自动去除重复的关键字
	//set<int> numbers(array, array + 10);
	set<int> numbers{2,1,6,7,2,1,3,4,5,8};
	display(numbers);
	//set不支持下标访问运算符
	//cout << numbers[0] << endl;
	set<int>::iterator sit = numbers.begin();
	++sit;
	cout << "*sit = " << *sit << endl;
	//查找元素 时间复杂度是O(logN) 二分查找 底层实现是红黑树
	//----》近似动态平衡二叉树 -----》左右子树高度差不会超过1
	// 对节点的调整:
	//		左旋
	//		右旋
	//红黑树:
	//1. 节点不是红色就是黑色
	//2. 根节点是黑色的
	//3. 叶子节点是黑色
	//4. 如果一个节点是红色，其左右孩子节点必须是黑色
	//5. 从根节点到叶子节点上的所有路径要保证黑色节点的个数相同
	size_t cnt = numbers.count(1);
	cout << cnt << endl;
	size_t cnt1 = numbers.count(9);
	cout << cnt1 << endl;
	set<int>::iterator it = numbers.find(2);
	if(it == numbers.end()){
		cout << "该值不在列表中" << endl;
	}
	else{
		cout << "已找到*it = " << *it << endl;
	}
	//插入一个元素
	std::pair<set<int>::iterator,bool> ret = numbers.insert(11);
	if(ret.second){
		cout << "元素插入成功 : " << *ret.first << endl;
	}
	else{
		cout << "元素插入失败，元素已存在" << endl;
	}
	//添加迭代器范围的元素
	vector<int> vec{1,2,3,15,16,17};
	numbers.insert(vec.begin(),vec.end());
	display(numbers);
	cout << "删除元素" << endl;
	auto it123 = numbers.begin();
	++it123;
	numbers.erase(it123);
	display(numbers);
}
void test1()
{
	int array[] = {2,1,6,7,2,1,3,4,5,8};
	//set引入第二个模板参数进行降序的方式进行排序
	//自动去除重复的关键字
	set<int,std::greater<int>> numbers(array, array + 10);
	display(numbers);
}
void test2()
{
//	set<Point> points{
//	Point(1,2),
//	Point(3,4),
//	Point(-1,-2),
//	Point(0,2),
//	Point(1,2)
//	};
//	set<Point,std::greater<Point>> points{
//	Point(1,2),
//	Point(3,4),
//	Point(-1,-2),
//	Point(0,2),
//	Point(1,2)
//	};
	set<Point,PointComparator> points{
	Point(1,2),
	Point(3,4),
	Point(-1,-2),
	Point(0,2),
	Point(1,2)
	};
	display(points);
}
int main(void)
{
	test00();
	test0();
	test1();
	test2();
	return 0;
}

