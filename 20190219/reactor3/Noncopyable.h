 ///
 /// @file    Noncopyable.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-10 21:14:43
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable() {}

	Noncopyable(const Noncopyable &)=delete;
	Noncopyable & operator=(const Noncopyable & )=delete;
};
}// end of namespace wd

#endif
