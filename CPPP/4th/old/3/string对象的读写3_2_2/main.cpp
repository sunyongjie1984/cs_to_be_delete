#include <iostream>
#include <string>
using namespace std;
/*
using std::cin;
using std::cout;
using std::string;
using std::endl;
*/
/*
int main() // 这个程序帮助了解一些流的事情。
{          // 输入hello world 回车 再输入hello world情况要好好看一下
	string s; // 然后看main函数2，别外的例子。
	cin >> s;
	cout << s << endl; // 感觉此处的endl并没有刷新流中的内容，因为第一次的hello world中的world
                       // 还是写到了s2里面，这是为什么呢？
	string s2, s3;
	cin >> s2 >> s3;
	cout << s2 << ' ' << s3 << endl;
	return 0;
}
*/
int main()
{
	string s; // 我采用三种输入的方法：一是：1. hello 回车 3 回车 hello world 回车
	cin >> s; // 二是：hello 3 hello world 回车
	cout << s << endl; // 三是：hello world hello world
                       // 结果是前两种都能够正常输出，我觉得就是流没有出现错误，第三种
	int a;             // 就出错了
	cin >> a;
	cout << a << endl;

	string s2, s3;
	cin >> s2 >> s3;
	cout << s2 << ' ' << s3 << endl;

	return 0;
}