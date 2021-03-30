 ///
 /// @file    for_each.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-07 15:01:32
 ///
 
#include <iostream>
#include <algorithm>
#include<vector>
using std::cout;
using std::endl;
using std::for_each;
using std::vector;
//传引用的话是可以修改numbers容器里面的值的
void display(int number)
{
	cout << number << " ";
}
int main(void)
{
	vector<int> numbers{2,1,2,3};
	std::sort(numbers.begin(),numbers.end());
	//for_each(numbers.begin(),numbers.end(),display);
	for_each(numbers.begin(),numbers.end(),[](int number)
			{
			cout << number << " ";
			});
	cout << endl;

	auto ret = std::count(numbers.begin(),numbers.end(),2);
	cout << ret << endl;
	auto it = std::find(numbers.begin(),numbers.end(),3);
	cout << "*it = " << *it << endl;
	auto it1 = std::binary_search(numbers.begin(),numbers.end(),5);
	cout << it1 << endl;
	return 0;
}
