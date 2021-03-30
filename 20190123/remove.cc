 ///
 /// @file    remove.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-07 15:14:11
 ///
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::vector;
using std::remove_if;
using std::cout;
using std::endl;
using std::ostream_iterator;

int main(void)
{
	vector<int> numbers{1,2,3,4,5,6,7,8};
//	auto it = remove_if(numbers.begin(),numbers.end(),[](int number){
//				return number > 4;
//			});
	std::less<int> lt;//lt(4,rhs);
//	auto it = remove_if(numbers.begin(),numbers.end(),std::bind1st(lt,4));
	auto it = remove_if(numbers.begin(),numbers.end(),std::bind2nd(lt,4));
	numbers.erase(it,numbers.end());
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	cout << endl;
	return 0;
}
