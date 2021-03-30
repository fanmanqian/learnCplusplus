 ///
 /// @file    Singleton.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-09 10:08:44
 ///
#include <stdlib.h> 
#include <iostream>
using std::cout;
using std::endl;
//单例对象自动释放:
//方法2: atexit
class Singleton
{
public:
	static Singleton * getInstance()
	{
		if(nullptr == _pInstance)
		{
			_pInstance = new Singleton();
			::atexit(destroy);
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance)
			delete _pInstance;
	}
	void print()const
	{
		cout << "object1" << endl;
	}
private:
	Singleton()
	{
		cout << "Singleton()" << endl;
	}
	~Singleton()
	{
		cout << "~Singleton()" << endl;
	}
private:
	static Singleton* _pInstance;
};
//Singleton* Singleton::_pInstance = nullptr; 饿汉模式
Singleton* Singleton::_pInstance = Singleton::getInstance();//饱汉模式
int main(void)
{
	Singleton::getInstance()->print();
	return 0;
}
