 ///
 /// @file    Noncopyable.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-02 17:01:31
 ///


#ifndef __NONCOPYABLE__
#define __NONCOPYABLE__

namespace wd
{
class Noncopyable
{
public:
	Noncopyable() {}
	~Noncopyable() {}

	Noncopyable(const Noncopyable &) = delete;
	Noncopyable & operator=(const Noncopyable &) = delete;
};
}//end of namespace
#endif
