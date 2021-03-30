 ///
 /// @file    Singleton.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-09 10:08:44
 ///
#include <pthread.h>
#include <stdlib.h> 
#include <iostream>
using std::cout;
using std::endl;
//单例对象自动释放:
//方法2: atexit + pthread_once
//   > 平台相关性
class Singleton
{
public:
	static Singleton * getInstance()
	{
		pthread_once(&_once,init);
		return _pInstance;
	}

	static void init()
	{
		_pInstance = new Singleton();
		::atexit(destroy);
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
	static pthread_once_t _once;
};
Singleton* Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;
int main(void)
{
	Singleton::getInstance()->print();
	return 0;
}
