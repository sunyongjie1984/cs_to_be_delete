#include <iostream>
using namespace std;
int counter; // 对于test这个文件中的全局变量counter用两种在此工程的  
void fun()   // 的其它文件中使用的方法，一种就是这种，一种是下面的
{
//	extern int counter; // 第二种方法
	extern const int counter2; 
	++counter;
	cout << counter << endl;
	cout << counter2 << endl;
//	return 0;
}