 ///
 /// @file    Dict.h
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-12 14:25:37
 ///
 
#ifndef __DICT_H__
#define __DICT_H__
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <set>
using std::string;
using std::map;
using std::vector;
using std::pair;
using std::set;
using std::make_pair;

class Dict{
public:
	Dict(const string & lib,const string & data)
	: _libPath(lib)
	, _outPath(data)
	{}

	void genDict();
	void genIndex();
	void output();
	map<string,set<int>> getIndex();
	vector<pair<string,int>> getVec();

private:
	map<string,int> _dict;
	string _libPath;
	string _outPath;
	vector<pair<string,int>> _vec;
	map<string,set<int>> _index;
};
#endif
