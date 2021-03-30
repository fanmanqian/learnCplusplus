 ///
 /// @file    cowtest.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-09 14:48:26
 ///
 
#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
 
class String
{
public:
	String()
	: _pstr(new char[5]() + 4)
	{
		cout << "String()" << endl;
		//*(int*(_pstr - 4)) = 1;
		initRefcount();
	}
	

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 5]() + 4)
	{
		strcpy(_pstr,pstr);
		//*(int*(_pstr - 4)) = 1;
		initRefcount();
		cout << "String(const char * pstr)" << endl;
	}


	String(const String & rhs)
	 : _pstr(rhs._pstr)
	{
	    increaseRefcount();
		cout << "String(const String & rhs)" << endl;
	}


	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &)" << endl;
		if(this!=&rhs)//自复制
		{
		//	decreaseRefcount();//释放左操作数空间
		//	if(refCount == 0)
		//	{
		//		delete [] (_pstr-4);
		//	}
			release();
			_pstr = rhs._pstr;//浅拷贝
			increaseRefcount();
		}
		return *this;
	}


	~String()
	{
		release();
		cout << "~String()" << endl;
	}

	const char * c_str() const
	{
		return _pstr;
	}

	size_t size() const
	{
		return strlen(_pstr);
	}
	int refCount() const
	{
		return *(int*)(_pstr - 4);
	}

	char & operator[](size_t idx)
	{
		if(idx < size()){
			if(refCount() > 1){//共享字符串
				char * _ptmp = new char[size() + 5]() + 4;//进行深拷贝
				strcpy(_ptmp,_pstr);
				decreaseRefcount();
				_pstr = _ptmp;
				initRefcount();
			}
			return _pstr[idx];
		}else{
			static char nullchar = '\0';
			return nullchar;
		}
	}
private:
	void initRefcount()
	{
		*(int*)(_pstr - 4 ) = 1;
	}

	void increaseRefcount()
	{
		++*(int*)(_pstr - 4);
	}

	void decreaseRefcount()
	{
		--*(int*)(_pstr - 4);
	}


	void release()
	{
		decreaseRefcount();
		if(refCount() == 0){
			delete [] (_pstr-4);
			cout << ">> delete heap data!!!" << endl;
		}
	}
	friend std::ostream & operator<<(std::ostream & os,const String & rhs);
private:
	char * _pstr;//永远指向字符串内容本身
};


std::ostream & operator<<(std::ostream & os,const String & rhs)
{
//	printf("str's address = %p\n", rhs._pstr);
	os << rhs._pstr;
	return os;
}


int main(void)
{
	String s1("hello,world");
	String s2 = s1;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1's refCount = " << s1.refCount() << endl;
	cout << "s2's refCount = " << s2.refCount() << endl;
	printf("s1's address = %p\n",s1.c_str());
	printf("s2's address = %p\n",s2.c_str());

	String s3("hebeihuwan");
	cout << ">> 执行String s3 = s1 之后: " << endl;
	s3 = s1;
	cout << "s3 = " << s3 << endl;
	cout << "s3's refCount = " << s3.refCount() << endl;
	printf("s3's address = %p\n",s3.c_str());
	cout << endl << "对s3[0]执行写操作: " << endl;
	s3[0] = 'H';
	cout << "s3 = " << s3 << endl;
	cout << "s3's refCount = " << s3.refCount() << endl;
	printf("s3's address = %p\n",s3.c_str());
	cout << endl << "对s1[0]执行读操作:" << endl;
	cout << s1[0] << endl;
	cout << "s1's refCount = " << s1.refCount() << endl;
	cout << "s2's refCount = " << s2.refCount() << endl;
	printf("s1's address = %p\n",s1.c_str());
	printf("s2's address = %p\n",s2.c_str());
	cout << "s3's refCount = " << s3.refCount() << endl;
	printf("s3's address = %p\n",s3.c_str());
	return 0;
}
