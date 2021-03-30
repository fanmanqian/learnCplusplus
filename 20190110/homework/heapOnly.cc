 ///
 /// @file    stackOnly.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-11 11:10:07
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
 
class Student
{
public:
	Student(int id,const char * name)
	: _id(id)
	, _name(new char[strlen(name) + 1]())
	{
		strcpy(_name,name);
		cout << "Student(int ,const char *)" << endl;
	}
	void destroy()
	{
		cout << "destroy" << endl;
		delete this;
	}
	void print() const
	{
		cout << "id = " << _id <<  endl;
		cout << "name = " << _name << endl;
	}
private:
	~Student()
	{
		delete [] _name;
		cout << "~Student" << endl;
	}
private:
	int _id;
	char * _name;
};
int main(void)
{
	Student s1(123,"xiaoming");
	s1.print();
	Student * s2 = new Student(456,"xiaoli");
	s2->print();
	s2->destroy();
	return 0;
}
