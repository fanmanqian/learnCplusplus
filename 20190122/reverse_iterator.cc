 ///
 /// @file    reverse_iterator.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-06 12:11:27
 ///
 
#include <iostream>
#include <iterator>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::reverse_iterator;


int main(void)
{
	vector<int> vec{1,2,3};
	vector<int>::reverse_iterator rit = vec.rbegin();
	while(rit!=vec.rend()){
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	return 0;
}
