 ///
 /// @file    Singleton.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-09 10:08:44
 ///
 
#include <iostream>
using std::cout;
using std::endl;
//需要创建一个对象，需要一个类
//当对象被销毁时，析构函数会被自动调用 
//专为Singleton而生的
//单例对象自动释放:
//方法1: 嵌套类 + 静态对象
class Singleton
{
public:
	static Singleton * getInstance()
	{
		if(nullptr == _pInstance)
			_pInstance = new Singleton();
		return _pInstance;
	}

	void print()const
	{
		cout << "object1" << endl;
	}
private:
	class AutoRelease
	{
		public:
			AutoRelease()
			{
				cout << "AutoRelease()" << endl;
			}
			~AutoRelease()
			{
				cout << "~AutoRelease()" << endl;
				delete _pInstance;
			}
	};
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
	static AutoRelease _auto;
};
Singleton* Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_auto;
int main(void)
{
	Singleton::getInstance()->print();
	return 0;
}
