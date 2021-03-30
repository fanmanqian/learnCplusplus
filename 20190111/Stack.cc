 ///
 /// @file    Stack.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-25 12:43:28
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Stack
{
public:
	Stack(int size = 10)
	: _size(size)
	, _top(-1)
	, _data(new int[_size]())
	{

	}

	~Stack()
	{
		delete [] _data;
	}

	bool empty() const
	{
		return _top == -1;
	}

	bool full() const
	{
		return _top == _size - 1;
	}

	void push(int value)
	{
		//判断栈是否满
		if(!full()){
			_data[++_top] = value;
		}
	}

	void pop()
	{
		if(!empty()){
			--_top;
		}
	}

	int top()
	{
		return _data[_top];
	}

private:
	int _size;
	int _top;
	int * _data;
};
int main(void)
{
	 Stack stack;
	 cout << "栈是否为空? " << stack.empty() << endl;
	 stack.push(1);
	 cout << "栈是否为空? " << stack.empty() << endl;
	 for(int idx=2; idx!=12; ++idx)
	 {
		stack.push(idx);
	 }
	 cout << "栈是否满? " << stack.full() << endl;
	 while(!stack.empty())
	 {
		 cout << stack.top() << endl;
		 stack.pop();
	 }
	 cout << "栈是否为空? " << stack.empty() << endl;
	 return 0;
}
