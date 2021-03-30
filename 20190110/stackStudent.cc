 ///
 /// @file    Student.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-17 10:38:32
 ///

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
 
//只能生成栈对象
//  >意味着该对象只能放在栈上,不能放在堆上
//采取的操作是: 将operator new/delete 放在private区域
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

	~Student()
	{
		delete [] _name;
		cout << "~Student" << endl;
	}
private:
	void * operator new(size_t size);
	void operator delete(void * pret);

private:
	int _id;
	char * _name;
};
int main(void)
{
	Student s2(101,"xiaohong");
	s2.print();
	//Student * s1 = new Student(100,"xiaoming");
	//s1->print();
	//delete s1;
	return 0;
}
