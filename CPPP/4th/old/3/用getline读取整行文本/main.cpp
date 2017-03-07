#include <iostream> // 些程序和读入未知数目的string对象一起学习
#include <string>
using namespace std;
int main()
{
	string line; // 表面上看这个程序能够一行一行地输出，而上一个程序
	while (getline(cin, line)) // 是一个词一个词的输出，还有好多的知识
	{                          // 要学习啊
		cout << line << endl;
	}

//	getline(cin, line);
//	cout << line << endl;
	return 0;
}