#include <iostream>
#include <string>
using namespace std;
int main()
{
	int i = 100;
	int sum = 0;
	for (i = 0; i != 10; ++i)
		sum += i;
	int j = 100; // 我想找个需要压栈出栈的东西，可能会改写i的内容的操作，但是不知道怎么做，^_^(@_@)
	cout << j << endl;
	cout << i << endl << sum << endl; // 太郁闷了，书上写的和我的IDE不一样关于语句作用域的问题。
	return 0;
}