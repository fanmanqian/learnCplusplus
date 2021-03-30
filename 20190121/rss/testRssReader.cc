 ///
 /// @file    testRssReader.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-22 20:21:05
 ///

#include "RssReader.h"
#include "tinyxml2.h"
int main(void)
{
	string filename("pagelib.txt");
	RssReader rss;
	rss.parseRss();
	rss.dump(filename);
	return 0; 
}
