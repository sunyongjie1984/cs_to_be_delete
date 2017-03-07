#include <iostream>
using namespace std;
int main()
{
	int i, j, ival;
	const int ci = i; // 这样子可以,但是不好，呵呵
//	1024 = ival; // error: literals are rvalues
//	i + j = ival; // error: arithmetic expressions are rvalues
//	ci = ival; // error: can't write to ci // 因为只读，对么?
	cout << ci << endl;
	return 0;
}