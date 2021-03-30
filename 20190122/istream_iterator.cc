 ///
 /// @file    istream_iterator.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-06 11:20:57
 ///
 
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::istream_iterator;
using std::ostream_iterator;
using std::copy;
using std::vector;


int main(void)
{
	vector<int> numbers;
	istream_iterator<int> isi(cin);
	copy(isi,istream_iterator<int>(),std::back_inserter(numbers));
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	return 0;
}
