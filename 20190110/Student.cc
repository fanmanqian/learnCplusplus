 ///
 /// @file    Student.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-17 10:38:32
 ///

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
 
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
		delete _name;
		cout << "~Student" << endl;
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


private:
	int _id;
	char * _name;
};
int main(void)
{
	Student * s1 = new Student(100,"xiaoming");
	s1->print();
	delete s1;
	return 0;
}
