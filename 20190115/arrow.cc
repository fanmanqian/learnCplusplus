 ///
 /// @file    arrow.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-08 08:53:10
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class Data
{
public:
	explicit
	Data(int data)
	: _data(data)
	{
		cout << "Data(int)" << endl;
	}

	int getData() const
	{
		return _data;
	}


	~Data()
	{
		cout << "~Data()" << endl;
	}
private:
	int _data;
};


class MiddleLayer
{
public:
	explicit
	MiddleLayer(Data * data)
	: _data(data)
	{
		cout << "MiddleLayer(Data*)" << endl;
	}

	//重载指针运算符
	Data * operator->()
	{
		return _data;
	}
	

	//重载解引用运算符
	Data & operator*()
	{
		return *_data;
	}

	~MiddleLayer()
	{
		delete _data;
		cout << "~MiddleLayer" << endl;
	}
private:
	Data * _data;
};


class ThirdLayer
{
public:
	explicit
	ThirdLayer(MiddleLayer * ml)
	: _ml(ml)
	{
		cout << "ThirdLayer(MiddleLayer)" << endl;
	}


	MiddleLayer & operator->()
	{
		return *_ml;
	}


	~ThirdLayer()
	{
		delete _ml;
		cout << "~ThirdLayer()" << endl;
	}
private:
	MiddleLayer * _ml;
};


int main(void)
{
	MiddleLayer m1(new Data(3));
	cout << (*m1).getData() << endl;
	cout << m1->getData() << endl;
	cout << (m1.operator->())->getData() << endl;
//	ThirdLayer t1(new MiddleLayer(new Data(10)));
//	cout << t1->getData() << endl;
//	cout << ((t1.operator->()).operator->())->getData() << endl;
	
	return 0;
}
