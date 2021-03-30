#include "Computer.h"
#include<iostream>
using std::cout;
using std::endl;

//创建全局的也可以
Computer gComputer("Mi", 6666);
int main()
{
	gComputer.print();
	cout << endl;
	Computer c1("lenoverrfav thinkpad",10000);
//	c1.setBrand("leovaughhgv thinkpado");
//	c1.setPrice(5555);
	c1.print();
	cout << endl;
	Computer * pc = new Computer("Macbook pro", 98999);
	pc->print();
	delete pc;//别忘了delete
	return 0;
}
