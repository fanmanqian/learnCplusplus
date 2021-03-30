 ///
 /// @file    Task.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-02-05 21:43:02
 ///
 
#ifndef __WD_TASK_H__
#define __WD_TASK_H__

namespace wd
{

class Task
{
public:
	virtual
	void process() = 0;

	virtual
	~Task()
	{}
};
}// end of namespace wd
#endif
