 ///
 /// @file    log4cpp1.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-01 10:39:40
 ///
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;
//输出到控制台
void test0()
{

	//控制日志输出格式
	PatternLayout * patternLayout = new PatternLayout();
	patternLayout->setConversionPattern("%d %c [%p] %m%n");

	//指定日志输出的目的地
	OstreamAppender * ostreamAppender = new OstreamAppender("console", &cout);
	ostreamAppender->setLayout(patternLayout);


	//日志记录器
	Category & root = Category::getRoot();
	//执行日志记录操作
	root.setAppender(ostreamAppender);
	root.setPriority(Priority::DEBUG);
	root.emerg("this is an emerg message");
	root.fatal("this is a fatal message");
	root.alert("this is a alert message");
	//回收内存
	Category::shutdown();
}
//既输入到文件也输入到控制台
void test1()
{

	//控制日志输出格式
	PatternLayout * patternLayout = new PatternLayout();
	patternLayout->setConversionPattern("%d %c [%p] %m%n");
	//由于有两个日志输出目的地所以需要2个patternLayout不然会报段错误
	PatternLayout * patternLayout2 = new PatternLayout();
	patternLayout2->setConversionPattern("%d %c [%p] %m%n");

	//指定日志输出的目的地
	OstreamAppender * ostreamAppender = new OstreamAppender("console", &cout);
	ostreamAppender->setLayout(patternLayout);

	FileAppender * fileAppender = new FileAppender("fileAppender","wd.log");
	fileAppender->setLayout(patternLayout2);


	//日志记录器
	Category & myCat = Category::getRoot().getInstance("myCat");
	myCat.addAppender(ostreamAppender);
	myCat.addAppender(fileAppender);
    myCat.setPriority(Priority::DEBUG);//Category的优先级

	//日志过滤器: 只有当每一条日志的优先级大于Category优先级时，该条日志才会被记录;否则，直接忽略
	
	//执行日志记录操作
	myCat.emerg("this is an emerg message");//每一条日志的优先级
	myCat.fatal("this is a fatal message");
	myCat.alert("this is a alert message");
	//回收内存
	Category::shutdown();
}
void test2()
{

	//控制日志输出格式
	PatternLayout * patternLayout = new PatternLayout();
	patternLayout->setConversionPattern("%d %c [%p] %m%n");
	//由于有两个日志输出目的地所以需要2个patternLayout不然会报段错误
	PatternLayout * patternLayout2 = new PatternLayout();
	patternLayout2->setConversionPattern("%d %c [%p] %m%n");

	//指定日志输出的目的地
	OstreamAppender * ostreamAppender = new OstreamAppender("console", &cout);
	ostreamAppender->setLayout(patternLayout);

	RollingFileAppender * rollingFileAppender = 
		new RollingFileAppender("rollingFileAppender",
				"wd1.log",
				5 *1024,
				3);
	rollingFileAppender->setLayout(patternLayout2);


	//日志记录器
	Category & myCat = Category::getRoot().getInstance("myCat");
	myCat.addAppender(ostreamAppender);
	myCat.addAppender(rollingFileAppender);
    myCat.setPriority(Priority::DEBUG);//Category的优先级

	//日志过滤器: 只有当每一条日志的优先级大于Category优先级时，该条日志才会被记录;否则，直接忽略
	
	//执行日志记录操作
	for(int idx = 0; idx!=400;++idx){
		myCat.emerg("this is an emerg message");//每一条日志的优先级
		myCat.fatal("this is a fatal message");
		myCat.alert("this is a alert message");
	}
	//回收内存
	Category::shutdown();
}
int main(void)
{
	//test0();
	test2();
	return 0;
}
