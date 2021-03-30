 ///
 /// @file    Singleton.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-22 14:14:39
 ///
 

#ifndef _WD_TEMPLATE_SINGLETON_H__
#define _WD_TEMPLATE_SINGLETON_H__

#include <iostream>
using std::cout;
using std::endl;
template<class T>
class Singleton
{
public:
	template<class... Args>
	static T * getInstance(Args...args)
	{
		if(nullptr == _pInstance){
			_ar;
			_pInstance = new T(args...);
		 }
		return _pInstance;
	}

private:
	Singleton(){
		cout << "Singleton()" << endl;
	}
	~Singleton()
	{
		cout << "~Singleton()" << endl;
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
				if(_pInstance){	
					cout << "~AutoRelease" << endl;
					delete _pInstance;
				}
			}
	};
private:
	static T * _pInstance;
	static AutoRelease _ar;
};
template<class T>
T * Singleton<T>::_pInstance = nullptr;
template<class T>
class Singleton<T>::AutoRelease Singleton<T>::_ar;
#endif
