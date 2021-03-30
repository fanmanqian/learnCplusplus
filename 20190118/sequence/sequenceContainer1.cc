 ///
 /// @file    sequenceContainer1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 13:55:43
 ///
 
#include <iostream>
#include <vector>
#include <deque>
#include <list>
using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;


template <class Container>
void display(const Container & c)
{
	for(auto & elem : c){//使用auto 要加上引用&符号 否则会进行复制
		cout << elem << " ";
	}
	cout << endl;
}
void test0() 
{
	//vector<int> numbers(10);
	//int array[] = {1,2,3,4,5,6,7,8,9,10};
	//vector<int> numbers(array,array+10);
	//vector<int> numbers{1,2,3,4,5,6};
	vector<int> numbers = {1,2,3,4,5,6};
	//通过迭代器方式进行访问
	vector<int>::const_iterator cit;
	cout << "numbers's size = " << numbers.size() << endl;
	cout << "numbers's capacity = " << numbers.capacity() << endl;
	for(cit = numbers.begin(); cit != numbers.end(); ++cit){
		cout << *cit << " ";
	}

	//auto自动推导
	auto it = numbers.begin();
	for(; it!= numbers.end(); ++it){
		cout << *it << " ";
	}
	cout << endl;
	//C++11 记住要加上引用
	for(auto & elem : numbers){
		cout << elem << " ";
	}
	cout << endl;
	cout << "使用模板" << endl;
	display(numbers);
}
void test1() 
{
	//deque<int> numbers(10,1);
	//int array[] = {1,2,3,4,5,6,7,8,9,10};
	//deque<int> numbers(array,array+10);
	//deque<int> numbers{1,2,3,4};
	deque<int> numbers = {1,2,3,4};
	deque<int>::const_iterator cit;
	for(cit = numbers.begin(); cit != numbers.end(); ++cit){
		cout << *cit << " ";
	}
	cout << endl;
	cout << "numbers[0] = " << numbers[0] << endl;
	cout << "使用模板" << endl;
	display(numbers);
}
void test2() 
{
	//list<int> numbers(10,1);
	//int array[] = {1,2,3,4,5,6,7,8,9,10};
	//list<int> numbers(array,array+10);
	//list<int> numbers{1,2,3,4};
	list<int> numbers = {1,2,3,4};
	list<int>::const_iterator cit;
	for(cit = numbers.begin(); cit != numbers.end(); ++cit){
		cout << *cit << " ";
	}
	cout << endl;
	cout << "使用模板" << endl;
	display(numbers);
}
int main(void)
{
	test0();
	test1();
	test2();
	return 0;
}
