 ///
 /// @file    Dict.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-12 14:25:37
 ///
 
#ifndef __DICT_H__
#define __DICT_H__
#include<string>
using std::string;
class Dict{
public:
	Dict(const string & lib,const string & data)
	: _libpath(lib)
	, _outPath(data)
	{}

	void genDict();
	void genIndex();
	void output();
private:
	map<string,int> _dict;
	string _libPath;
	string _outPath;
	vector<pair<string,set<int>>> _vec;
	map<string,set<int>> _index;
};
#endif
