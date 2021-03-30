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
	shared_ptr<Parent> pParent;
};
int main(void)
{
	shared_ptr<Parent> pPa(new Parent());
	shared_ptr<Child> pCh(new Child());
	cout << "pPa's refcount = " << pPa.use_count() << endl;
	cout << "pCh's refcount = " << pCh.use_count() << endl;
	pPa->pChild = pCh;
	pCh->pParent = pPa;
	cout << "pPa's refcount = " << pPa.use_count() << endl;
	cout << "pCh's refcount = " << pCh.use_count() << endl;
	return 0;
}
