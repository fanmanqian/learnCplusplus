 ///
 /// @file    templateClass.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-15 13:16:41
 ///
 
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string; 

template<class T,size_t size=10>
class Stack
{
public:
	Stack()
	: _top(-1)
	, _size(size)
	, _data(new T[_size]())
	{ }

	~Stack()
	{
		if(_data){
			delete [] _data;
		}
	}

	bool empty() const
	{
		return _top==-1;
	}
	bool full() const
	{
		return _top == _size - 1;
	}
	void push(T value);
	void pop()
	{
		if(!empty()){
			--_top;
		}else{
			cout << "栈为空" << endl;
		}
	}
	T getTop()
	{
		return _data[_top];
	}

private:
	int _top;
	size_t _size;
	T * _data;
};

template<class T,size_t size>//这行不能有默认参数
void Stack<T,size>::push(T value)
{
	if(!full()){
		++_top;
		_data[_top] = value;
	}
}

int main(void)
{
//	Stack<int,10> s;
//	cout << "栈是否为空: " << s.empty() << endl;
//	s.push(1);
//	cout << "栈是否为空: " << s.empty() << endl;
//	for(int idx = 2; idx <= 12; ++idx){
//		s.push(idx);
//	}
//	cout << "栈是否满: " << s.full() << endl;
//	cout << "栈顶元素为: " << s.getTop() << endl;
//	while(!s.empty()){
//		cout << s.getTop() << endl;
//		s.pop();
//	}
//	cout << "栈是否为空: " << s.empty() << endl;	
	Stack<string,9> s;
	cout << "栈是否为空: " << s.empty() << endl;
	string al="aa";
	s.push(al);
	cout << "栈是否为空: " << s.empty() << endl;
	for(int idx = 1; idx <= 12; ++idx){
		s.push(string(2,'a' + idx));
	}
	cout << "栈是否满: " << s.full() << endl;
	cout << "栈顶元素为: " << s.getTop() << endl;
	while(!s.empty()){
		cout << s.getTop() << endl;
		s.pop();
	}
	cout << "栈是否为空: " << s.empty() << endl;	
	return 0;
}
