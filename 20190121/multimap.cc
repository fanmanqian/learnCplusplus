 ///
 /// @file    multimap.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-04 10:18:00
 ///
 
#include <iostream>
#include <map>
#include <string>
using std::string;
using std::multimap;
using std::cout;
using std::endl;
template<class T>
void display(const T & c)
{
	for(auto & elem : c)
	{
		cout << elem.first << "----->" << elem.second << endl;
	}
}
int main(void)
{
	multimap<int,string> cities{
		std::pair<int,string>(1,"北京"),
		std::pair<int,string>(2,"长沙"),
		std::pair<int,string>(2,"重庆"),
		std::make_pair(3,"苏州"),
		std::make_pair(4,"上海")
	};
	display(cities);
	//multimap不支持下标访问运算符
	//cout << "cities[1] = " << cities[1] << endl;//O(logN)
	//查找元素的两种方法count 和 find
	auto ret = cities.count(2);
	if(ret){
		cout << "查找成功" << endl;
	}
	else{
		cout << "查找失败" << endl;
	}
	auto ret1 = cities.find(2);
	if(ret1 == cities.end()){
		cout << "查找失败" << endl;
	}
	else{
		cout << "查找成功" << endl;
	}
	//insert方法 有返回值是迭代器 也可以直接插入不返回 因为multimap不会有插入失败的情况
	//auto ret = cities.insert(std::make_pair(2,"日本"));
	//cout << "ret->first" << "---->" << ret->second << endl;
	//
	display(cities);
	return 0;
}
