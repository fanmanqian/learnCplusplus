 ///
 /// @file    map.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-04 10:18:00
 ///
 
#include <iostream>
#include <map>
#include <string>
using std::string;
using std::map;
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
	map<int,string> cities{
		std::pair<int,string>(1,"北京"),
		std::pair<int,string>(2,"长沙"),
		std::make_pair(3,"苏州"),
		std::make_pair(4,"上海")
	};
	display(cities);
	cout << "cities[1] = " << cities[1] << endl;//O(logN)
	//访问map中的元素，可以使用下标访问运算符
	//下标访问运算符功能:
	// 1.可以查找相应关键字对应的值:如果pair存在，则直接输出对应的值
	// 如果不存在，则创建一个相应关键字的pair，对应的value会调用相应类型的默认构造函数
	// 2.可以修改相应关键字对应的value
	
	//查找元素的两种方法count 和 find
	auto ret = cities.count(11);
	if(ret){
		cout << "查找成功" << endl;
	}
	else{
		cout << "查找失败" << endl;
	}
	auto ret1 = cities.find(11);
	if(ret1 == cities.end()){
		cout << "查找失败" << endl;
	}
	else{
		cout << "查找成功" << endl;
	}
	//insert方法
	std::pair<map<int,string>::iterator,bool> ret2 = cities.insert(std::make_pair(2,"重庆"));
	//auto ret = cities.insert(std::make_pair(5,"重庆"));
	if(ret2.second){
		cout << "插入成功" << ret2.first->first << "--->" << ret2.first->second << endl;
	}
	else{
		cout << "插入失败" << ret2.first->first << "--->" << ret2.first->second << endl;	
	}
	return 0;
}
