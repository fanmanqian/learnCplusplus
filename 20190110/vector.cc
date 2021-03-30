 ///
 /// @file    vector.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-23 08:51:16
 ///
 
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


void printCapacity(vector<int> & vec)
{
	cout << "vec's size : " << vec.size() << endl
		 << "vec's capacity: " << vec.capacity() << endl;
}

int main(void)
{
	//动态数组可以自动扩容 但扩容是有开销的 
	//策略(扩容的原理):
	//当size == capacity 时，就再去开辟新的空间 2 * size
	//再把原来的空间元素复制到新空间，并释放原来的空间
	//最后在新空间的末尾添加新的元素
	vector<int> vec;
	vec.reserve(60);//提前开辟好空间，之后再去使用就不会再频繁的动态扩容 动态扩容是有开销的
	printCapacity(vec);
	vec.push_back(1);
	printCapacity(vec);
	vec.push_back(2);
	printCapacity(vec);
	vec.push_back(3);
	printCapacity(vec);
	vec.push_back(4);
	printCapacity(vec);
	vec.push_back(5);
	printCapacity(vec);
	//idx = 0 idx的范围必须在[0,size) 下面的使用才是正确的
	//numbers[idx] = 0
	return 0;
}
