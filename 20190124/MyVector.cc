 ///
 /// @file    MyVector.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-08 14:12:59
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
 
template<class T>
class Vector
{
public:
	typedef T value_type;
	typedef T * iterator;
	Vector()
	: _start(nullptr)
	, _finish(nullptr)
	, _end_of_storage(nullptr)
	{}

	~Vector();
	iterator begin() { return _start; }
	iterator end() { return _finish; }
	int size() const { return _finish - _start; }
	int capacity() const { return _end_of_storage - _start; }
	void push_back(const T & t);
	void pop_back();
private:
	void reallocate();
private:
	static std::allocator<T> _alloc;
	T * _start;
	T * _finish;
	T * _end_of_storage;
};

template<class T>
Vector<T>::~Vector()
{
	if(_start) {
		while(_start != _finish) {
			_alloc.destroy(--_finish);
		}
		_alloc.deallocate(_start,capacity());
	}
}
template<class T>
std::allocator<T> Vector<T>::_alloc;

template<class T>
void Vector<T>::push_back(const T & t)
{
	if(size() == capacity()) {
		reallocate();
	}
	if(size() < capacity()) {
		_alloc.construct(_finish++,t);
	}
}

template<class T>
void Vector<T>::pop_back()
{
	if(size() > 0) {
		_alloc.destroy(--_finish);
	}
}

template<class T>
void Vector<T>::reallocate()
{
	int oldCapacity = capacity();
	int newCapacity = 2 * oldCapacity > 0 ? 2 * oldCapacity : 1;
	T * ptmp = _alloc.allocate(newCapacity);
	if(_start) {
		std::uninitialized_copy(_start,_finish, ptmp);
		while(_finish!=_start) {
			_alloc.destroy(--_finish);
		}
	}
	_start = ptmp;
	_finish = _start + oldCapacity;
	_end_of_storage = _start + newCapacity;
}

template<class Container>
void display(const Container  & c)
{
	cout << "vec's size = " << c.size() << endl;
	cout << "vec's capacity = " << c.capacity() << endl;
}


class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{

	}

	Point(const Point & rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout << "Point(const Point & rhs)" << endl;
	}
	
	~Point()
	{
		cout << "~Point()" << endl;
	}

	int getX() const
	{
		return _ix;
	}
	
	int getY() const
	{
		return _iy;
	}
	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};
std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix << ","
	   << rhs._iy << ")";
	return os;
}

int main(void)
{
	Vector<int> numbers;
	numbers.push_back(1);
	display(numbers);
	numbers.push_back(2);
	display(numbers);
	numbers.push_back(3);
	display(numbers);
	numbers.push_back(4);
	display(numbers);
	numbers.push_back(5);
	display(numbers);
	for(auto & elem : numbers) {
		cout << elem << " ";
	}
	cout << endl;
	Vector<Point> points;
	points.push_back(Point(1,2));
	display(points);
	points.push_back(Point(3,4));
	display(points);
	points.push_back(Point(5,6));
	display(points);
	points.push_back(Point(7,8));
	display(points);
	points.push_back(Point(9,10));
	display(points);
	for(auto & elem : points) {
		cout << elem << " ";
	}
	cout << endl;

	return 0;
}
