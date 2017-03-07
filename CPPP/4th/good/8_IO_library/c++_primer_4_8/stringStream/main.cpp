#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std; 

int main()
{
	string str("123 456");
	istringstream iss(str);   //内存流中的内容是str的副本，不是引用
	// 流的>>操作符可自动转化为int,string等类型，很方便
	// int itmp;
	// while (iss >> itmp)   //读出，然后自动转化为int型
	//      cout << itmp + 1 << endl;
	//cout << "................................................\n";

	string strtmp;
	while(iss >> strtmp)  //读出，然后自动转化为string型
		cout << strtmp << endl;

}