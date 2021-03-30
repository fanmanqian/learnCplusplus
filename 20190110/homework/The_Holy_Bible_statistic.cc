 ///
 /// @file    The_Holy_Bible_statistic.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-11 11:49:10
 ///

#include <map>
#include <fstream>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::map;

class Dictionary
{
public:
	void read(const string & filename);
	void store(const string & filename);
private:
	map<string,int> mp;
};
void Dictionary::read(const string & filename)
{
	ifstream ifs(filename);
	string line;
	while(getline(ifs,line))
	{
		string word;
		for(size_t idx = 0; idx < line.size(); ++idx)
		{
			if((line[idx]>='a'&&line[idx]<='z')||(line[idx]>='A'&&line[idx]<='Z')){
				word+=line[idx];
			}
			else {
				if(word != ""){
					mp[word]++;
				}
				word="";
			}
		}
	}
	ifs.close();
}

void Dictionary::store(const string & filename)
{
	ofstream ofs(filename);
	for(map<string,int>::iterator it = mp.begin();it!=mp.end();++it){
		ofs << it->first << " " << it->second <<  endl;
	}
	ofs.close();
}

int main(void)
{
	Dictionary d;
	const string source = "./The_Holy_Bible.txt";
	const string dest = "./statistic_result.txt";
	d.read(source);
	d.store(dest);
	return 0;
}
