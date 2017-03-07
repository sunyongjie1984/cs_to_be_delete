// 虽然是一个小小的程序，可是却反映了一个事实，容器可以动态的定义大小长度
// 如果是数组是不能够实现这样的操作的。

#include <iostream>
#include <string> // 这里用到string的构造函数，可能是你不加这个头文件是不行的。
#include <vector>
using namespace std;
int main()
{
	vector<string> ivec(2,"I Love China!");
	// 标准无限循环
	for (vector<string>::size_type ix = 0; ix != ivec.size(); ix++)
	{
		ivec.push_back("syj"); // 是不是这就是一个算法
		cout << ivec[ix];
	}
	return 0;
}