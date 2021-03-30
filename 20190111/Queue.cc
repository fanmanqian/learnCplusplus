 ///
 /// @file    Queue.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-27 10:04:09
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Queue
{
public:
	Queue(int size = 10)
	: _size(size)
	, _front(0)
	, _rear(0)
	, _data(new int[_size]())
	{

	}
	~Queue()
	{
		delete [] _data;
	}

	bool empty() const
	{
		return _front == _rear;
	}

	bool full() const
	{
		return _front == (_rear + 1) % _size;
	}

	void push(int value)
	{
		if(!full())
		{
			_data[_rear++] = value;
			_rear %= _size;
		}else{
			cout << "queue is full ,can not push more data!" << endl;
		}
	}

	void pop()
	{
		if(!empty())
		{
			_front++;
			_front %= _size;
		}else
		{
			cout << "queue is empty!" << endl;
		}
	}

	int front() const
	{
		return _data[_front];
	}
	
	int back() const
	{
		return _data[(_rear - 1 + _size) % _size];
	}
	
	int getRear()
	{
		return _rear;
	}
private:
	int _size;
	int _front;
	int _rear;
	int * _data;
};
int main(void)
{
	 Queue queue;
	 cout << "队列是否为空? " << queue.empty() << endl;
	 queue.push(1);
	 cout << "队列是否为空? " << queue.empty() << endl;
	 for(int idx=2; idx!=12; ++idx)
	 {
		queue.push(idx);
	 }
	 cout <<"rear的值: " << queue.getRear() << endl;
	 cout << "尾部元素: " << queue.back() << endl;
	 queue.pop();
	 queue.push(10);
	 cout <<"rear的值: " << queue.getRear() << endl;
	 cout << "尾部元素: " << queue.back() << endl;
	 cout << "栈是否满? " << queue.full() << endl;
	 while(!queue.empty())
	 {
		 cout << queue.front() << endl;
		 queue.pop();
	 }
	 cout << "队列是否为空? " << queue.empty() << endl;
	 return 0;
}
