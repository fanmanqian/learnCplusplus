 ///
 /// @file    multiDerivedVirtual.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-01-27 12:56:04
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class A
{
public:
	virtual void a() { cout << "A::a()" << endl; }
	virtual void b() { cout << "A::b()" << endl; }
	virtual void c() { cout << "A::c()" << endl; }
};

class B
{
public:
	virtual void a() { cout << "B::a()" << endl; }
	virtual void b() { cout << "B::b()" << endl; }
	void c() { cout << "B::c()" << endl; }
	void d() { cout << "B::d()" << endl; }	
};

class C:
public A
,public B
{
public:
	virtual void a() { cout << "C::a()" << endl; }
	virtual void c() { cout << "C::c()" << endl; }
	void d() { cout << "C::d()" << endl; }
};

int main(void)
{
	C c;
	A * pa = &c;
	cout << "pa = " << pa << endl;
	pa->a();//C::a()
	pa->b();//A::b()
	pa->c();//C::c()

	B * pb = &c;
	cout << "pb = " << pb << endl;//与pa不同 
	pb->a();//C::a()
	pb->b();//B::b()
	pb->c();//B::c()
	pb->d();//B::d()

	C * pc = &c;
	cout << "pc = " << pc << endl;//与pa相同 但是操作的是两个指针区域
	pc->a();//C::a()
	//pc->b();//二义性 到底是A::b() 还是B::b()
	pc->A::b();
	pc->B::b();
	pc->c();//C::c()
	pc->d();//C::d()
	return 0;
}
