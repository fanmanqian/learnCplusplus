 ///
 /// @file    Line.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-08 10:50:52
 ///
 
#ifndef __WD_LINE_H__
#define __WD_LINE_H__

class Line
{
public:
	Line(int,int,int,int);
	~Line();

	void printLine()const;
	
	class LineImpl;//前向声明
private:
	LineImpl * _pimpl;
};
#endif
