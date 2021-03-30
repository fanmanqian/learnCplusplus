 ///
 /// @file    Dict.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-12 14:28:26
 ///
 
#include "Dict.h"
#include <fstream>
#include <iostream>
using std::endl;
using std::ifstream;
using std::ofstream;


void Dict::genDict()
{
	ifstream ifs(_libPath);
	string line;
	while(ifs) {
		getline(ifs,line);
		string word;
		for(string::size_type idx = 0; idx < line.size();++idx) {
			if(line[idx]!=' ') {
				word += line[idx];
			}
			else {
				_dict[word]++;
				word.clear();
			}
		}
	}
}

void Dict::genIndex()
{
	for(auto & elem : _dict) {
		_vec.push_back(std::make_pair(elem.first,elem.second));
	}
	for(auto & elem : _vec) {
		string temp = elem.first;
		for(string::size_type idx = 0; idx < temp.size(); ++idx) {
			string tmp;
			tmp.push_back(temp[idx]);
			_index[tmp].insert(elem.second);
		}
	}
}

map<string,set<int>> Dict::getIndex()
{
	return _index;
}

vector<pair<string,int>> Dict::getVec()
{
	return _vec;
}

void Dict::output()
{
	ofstream ofs(_outPath);
	for(auto & elem : _dict) {
		ofs << elem.first << " " << elem.second << endl;
	}
}

