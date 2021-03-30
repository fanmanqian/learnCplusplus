 ///
 /// @file    test.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2021-03-12 14:36:40
 ///
 
#include "Dict.h"
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	const string _loc1 = "./The_Holy_Bible.txt";
	const string _loc2 = "./output.dat";
	Dict cd(_loc1,_loc2);
	cd.genDict();
	cd.output();
	cd.genIndex();
	map<string,set<int>> mp = cd.getIndex();
	for(auto & elem : mp) {
		cout << elem.first << " ";
		for(auto & elem1 : elem.second) {
			cout << elem1 << " ";
		}
		cout << endl;
	}
	return 0;
}
