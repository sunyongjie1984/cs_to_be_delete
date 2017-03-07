#include <iostream>
using namespace std;
int main()
{
	int ival = 1.01;         // 合法ival是1
//	int &rval1 = 1.01;       // cannot convert from 'const double' to 'int &'
	int &rval2 = ival;       // 合法 ival是1, rval2也是1，就是别名嘛。
	const int &rval3 = 2.1;  // 合法，const引用可以初始化为右值。 


	cout << rval2 << endl;
	cout << rval3 << endl;
	return 0;
}