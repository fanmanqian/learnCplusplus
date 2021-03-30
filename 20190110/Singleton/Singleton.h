 ///
 /// @file    Singleton.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-11-17 09:50:24
 ///
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
class Singleton
{
public:
	static Singleton * getInstance();
	static void destroy();
private:
	Singleton();
	~Singleton();
private:
	static Singleton * _pInstance;
};
#endif

