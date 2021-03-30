 ///
 /// @file    use_iterator.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-06 11:47:57
 ///
 
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <set>
using std::set;
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::ostream_iterator;
using std::back_insert_iterator;
using std::front_insert_iterator;
using std::insert_iterator;
using std::copy;


int main(void)
{
	vector<int> numbers1{1,2,3};
	list<int> numbers2{4,5,6};

	copy(numbers2.begin(),numbers2.end(),back_insert_iterator<vector<int>>(numbers1));
	copy(numbers1.begin(),numbers1.end(),ostream_iterator<int>(cout," "));
	cout << endl;

	copy(numbers1.begin(),numbers1.end(),front_insert_iterator<list<int>>(numbers2));
	copy(numbers2.begin(),numbers2.end(),ostream_iterator<int>(cout," "));
	cout << endl;

	vector<int> numbers3{1,3,5};	
	set<int> st{23,44,55};
	auto it = st.begin();
	++it;
	cout << *it << endl;
	copy(numbers3.begin(),numbers3.end(),insert_iterator<set<int>>(st,std::next(it)));
	copy(st.begin(),st.end(),ostream_iterator<int>(cout," "));
	cout << endl;
	return 0;
}
