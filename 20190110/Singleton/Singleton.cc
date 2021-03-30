 ///
 /// @file    Singleton.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-17 09:54:55
 ///
#include "Singleton.h" 
#include<iostream>
using std::endl;
using std::cout;
Singleton * Singleton::_pInstance = nullptr;
Singleton * Singleton::getInstance()
{
	if(nullptr == _pInstance){
		_pInstance = new Singleton();
	}
	return _pInstance;
}

void Singleton::destroy()
{
	if(_pInstance != nullptr)
	{
		delete _pInstance;
	}
}

Singleton::Singleton()
{
	cout << "Singleton()" << endl;
}
Singleton::~Singleton()
{
	cout << "~Singleton()" << endl;
}
