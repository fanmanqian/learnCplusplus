 ///
 /// @file    circle_ref.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-13 13:33:31
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

class Child;
class Parent
{
public:
	Parent()
	{
		cout << "Parent()" << endl;
	}
	~Parent()
	{
		cout << "~Parent()" << endl;
	}
	shared_ptr<Child> pChild;
};
class Child
{
public:
	Child()
	{
		cout << "Child()" << endl;
	}
	~Child()
	{
		cout << "~Child()" << endl;
	}
	weak_ptr<Parent> pParent;
};
int main(void)
{
	shared_ptr<Parent> pPa(new Parent());
	shared_ptr<Child> pCh(new Child());
	cout << "pPa's refcount = " << pPa.use_count() << endl;
	cout << "pCh's refcount = " << pCh.use_count() << endl;
	pPa->pChild = pCh;//sp = sp
	pCh->pParent = pPa;//wp = sp 这里不会导致引用计数加1 引用计数不变
					  // weak_ptr它知道被托管的对象是否还存活
	cout << "pPa's refcount = " << pPa.use_count() << endl;
	cout << "pCh's refcount = " << pCh.use_count() << endl;
	return 0;
}
