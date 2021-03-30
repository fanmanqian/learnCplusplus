 ///
 /// @file    mem_fn.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-07 17:11:40
 ///
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;

class Number
{
public:
	Number(int data)
	: _data(data)
	{}

	void display() const
	{
		cout << _data << " ";
	}

	bool isEven() const
	{
		return _data % 2 == 0;
	}

	bool isPrime() const
	{
		if(_data == 1){
			return false;
		}
		for(size_t idx = 2; idx <= _data / 2; ++idx){
			if(_data%idx==0){
				return false;
			}
		}
		return true;
	}

private:
	int _data;
};

int main(void)
{
	vector<Number> numbers;
	for(int idx = 1; idx <= 20; ++idx){
		numbers.push_back(Number(idx));
	}
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout << endl;

	numbers.erase(std::remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isEven)),numbers.end());
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout << endl;

	numbers.erase(std::remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isPrime)),numbers.end());
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout << endl;

	return 0;
}
