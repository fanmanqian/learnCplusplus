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
using std::multiset;
using std::string;
using std::vector;
template<class T>
void display(const T & c)
{
	for(auto & elem : c)
	{
		cout << elem << " ";
	}
	cout << endl;
}
void test1()
{
	int array[] = {2,1,6,7,2,1,3,4,5,8};
	//multiset引入第二个模板参数进行降序的方式进行排序
	//自动去除重复的关键字
	multiset<int> numbers{2,1,6,7,2,1,3,4,5,8};
	numbers.insert(9);
	numbers.insert(3);
	numbers.insert(3);
	auto it = numbers.lower_bound(3);//返回第一个3出现的位置
	auto it1 = numbers.upper_bound(3);//返回最后一个3出现的下一个位置
	while(it!=it1){
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//equal_range与之等效
	//std::pair<multiset<int>::iterator,multiset<int>::iterator> 
	auto ret = numbers.equal_range(3);
	while(ret.first!=ret.second){
		cout << *ret.first << " ";
		++ret.first;
	}
	cout << endl;
	//display(numbers);

}
int main(void)
{
//	test00();
//	test0();
	test1();
//	test2();
	return 0;
}

