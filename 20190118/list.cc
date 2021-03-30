 ///
 /// @file    list.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-16 13:43:34
 ///
 
#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;


template<class Container>
void display(const Container & c)
{
	for(auto & elem : c){
		cout << elem << " ";
	}
	cout << endl;
}

int main(void)
{
	list<int> numbers{8,7,9,1,1,0};
	cout << " >>reverse>>" << endl;
	numbers.reverse();
	display(numbers);
	cout << ">>unique>>" << endl;
	numbers.unique();
	display(numbers);
	//numbers.sort();
	std::less<int> lt;
	std::greater<int> gt;//函数对象 定制化操作
	numbers.sort(lt);
	list<int> numbers1{22,33,44,55};
	numbers.merge(numbers1);
	display(numbers);
//	display(numbers1);//numbers1没有了全部合并到numbers里面去了
	cout << " >>>splice " << endl;
	list<int> numbers2{41,42,43,44};
	list<int>::iterator it = numbers.begin();
//	++it;
//	++it;
//	numbers.splice(it,numbers2);
//	display(numbers);
//	it = numbers.begin();
//	++it;
//	++it;
//	list<int>::iterator it1 = numbers2.begin();
//	numbers.splice(it,numbers2,it1);
//	display(numbers);
	list<int>::iterator it2 = numbers.end();
	--it2;
	numbers.splice(numbers.begin(),numbers,it2);
	display(numbers);
	return 0;
}
