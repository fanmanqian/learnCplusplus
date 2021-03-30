 ///
 /// @file    String.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-14 13:03:28
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
class String
{
public:
	String & opeator+=(const String & rhs)
	{
		char * tmp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
		strcpy(tmp,_pstr);
		delete [] _pstr;
		strcat(tmp,rhs._pstr);
		_pstr = tmp;
		return *this;
	}
	string & operator+=(const char * pstr)
	{
		String tmp(pstr);
		*this += tmp;
		return *this;
	}
	
private:
	char * _pstr;
};
int main(void)
{

}
