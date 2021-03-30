 ///
 /// @file    Student.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-17 10:38:32
 ///

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//只能生成堆对象
//  > 该对象只能放在堆上，不能放在栈上
//采取的操作是：将析构函数私有化设置成private 在类的内部定义destroy销毁对象 delete this
class Student
{
public:
	Student(int id,const char * name)
		:_id(id),
		_name(new char[strlen(name) + 1]())
	{
		cout << "Student(id,name)" << endl;
		strcpy(_name,name);
	}
	void print() const
	{
		cout << "id: " << _id << endl
			 << "name: " << _name << endl;
	}

	void * operator new(size_t size)
	{
		void * pret = malloc(size);
		cout << "void * operator new" << endl;
		return pret;
	}

	void operator delete(void * pret)
	{
		free(pret);
		cout << "void * operator delete" << endl;
	}

	void destroy()
	{
		//this->~Student();//不能直接调用析构函数
		delete this;//销毁对象
	}

private:
	~Student()
	{
		delete _name;
		cout << "~Student" << endl;
	}
private:
	int _id;
	char * _name;
};
int main(void)
{
	Student * s1 = new Student(100,"xiaoming");
	s1->print();
	//delete s1;//如果将析构函数私有化了 这里就会error 因为这个操作是在类之外 我们需要把它放到类的里面去
	//Student s2(101,"xiaohong");//必须得能调用到析构函数才会成功创建该对象
	//s2.print();
	s1->destroy();
	return 0;
}
