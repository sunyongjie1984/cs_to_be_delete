#include <string>
#include <iostream>
using namespace std;
int main()
{
	string word; // 我知道这个while循环的意思是输入的如果不是字符串
	while (cin >> word) // 就会流出错，可是我试了整数，浮点数都是不
	{                   // 跳出循环，害得我只能用contral + z才退出来
		cout << word << endl; // CP_page72
	}

	return 0;
}