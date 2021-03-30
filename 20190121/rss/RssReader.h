 ///
 /// @file    RssReader.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-22 20:15:20
 ///
 
#ifndef __RSS_READER_H__
#define __RSS_READER_H__

#include <vector>
#include <string>
using std::vector;
using std::string;


struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};


class RssReader
{
public:
	void parseRss();//解析
	void dump(const string & filename);//输出
private:
	vector<RssItem> _rss;
};
#endif
