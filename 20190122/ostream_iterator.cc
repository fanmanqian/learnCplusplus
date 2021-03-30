 ///
 /// @file    ostream_iterator.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-06 11:18:23
 ///
 
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::copy;
using std::ostream_iterator;
using std::vector;


int main(void)
{
	vector<int> numbers{1,2,3};
	ostream_iterator<int> osi(cout," ");
	copy(numbers.begin(), numbers.end(), osi);
	return 0;
}
