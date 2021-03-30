 ///
 /// @file    observer.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-01 15:14:57
 ///

#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <list>
using std::cout;
using std::endl;
using std::list;
using std::find;
using std::string;
using std::unique_ptr;

class Observer;//前向声明
class Subject
{
public:
	virtual void attach(Observer * ob) =0;//添加观察者
	virtual void detach(Observer * ob) =0;//删除观察者
	virtual void notify() =0;//通知观察者

	virtual ~Subject() { cout << "~Subject()" << endl; }
};

class Observer
{
public:
	virtual
	void update()=0;

	virtual ~Observer() { cout << "~Observer()" << endl; }
};

class Ring
: public Subject
{
public:
	void attach(Observer * ob) {
		auto iter = find(_oblist.begin(),_oblist.end(),ob);
		if(iter == _oblist.end()) {
			_oblist.push_back(ob);
		}
	}

	void detach(Observer * ob) {
		auto iter = find(_oblist.begin(),_oblist.end(),ob);
		if(iter != _oblist.end()) {
			_oblist.erase(iter);
		}
	}
	
	void notify() 
	{
		for(auto & ob :_oblist) {
			ob->update();
		}
	}
	
private:
	list<Observer*> _oblist;
};

class Baby
: public Observer
{
public:
	Baby(const string & name)
	: _name(name)
	, _random(-1)
	{}
	
	void update()
	{
		::srand(::clock());
		_random = ::rand() % 100;
		if(_random < 30) {
			cout << ">>Baby " << _name
				 << " starting crying." << endl;
		}else{
			cout << ">>Baby " << _name
				 << " is awake." << endl;	
		}
	}

	~Baby()
	{
		cout << ">>Baby " << _name << endl;
	}
private:
	string _name;
	int _random;
};
class Nurse
: public Observer
{
public:
	Nurse(const string & name)
	: _name(name)
	, _random(-1)
	{}
	
	void update()
	{
		::srand(::clock());
		_random = ::rand() % 100;
		if(_random < 70) {
			cout << ">>nurse " << _name
				 << " starts to open the door." << endl;
		}else{
			cout << ">>nurse " << _name
				 << " is awake." << endl;	
		}
	}

	~Nurse()
	{
		cout << ">>nurse " << _name << endl;
	}
private:
	string _name;
	int _random;
};

class Guest
{
public:
	Guest(const string name)
	: _name(name)
	{

	}

	void knock(Ring & ring) 
	{
		cout << "Guest " << _name << "is knocking the door." << endl;
		ring.notify();
	}

private:
	string _name;
};
int main(void)
{
	Ring ring;
	unique_ptr<Observer> baby1(new Baby("dabao"));
	unique_ptr<Observer> baby2(new Baby("erbao"));
	unique_ptr<Observer> nurse(new Nurse("xiaoli"));

	ring.attach(baby1.get());
	ring.attach(baby2.get());
	ring.attach(nurse.get());
	Guest guest("fanman");
	guest.knock(ring);
	return 0;
}
