#include <vector>
#include <iostream>
using namespace std;
//using std::endl;
//using std::cout; // cout是一个对象
//using std::vector;
//using std::vector<int>::size_type; // size_type是一个类型，我在这里有些不清楚明白,上网查查吧！
//using std::vector<int>::iterator;
//using std::vector<int>::const_iterator;
int main()
{   // 类模板是不是也是一个类，好像我以前曾经得到过这样的结论，但是没有人告诉我是不是对的@.@~
	// vector是一个类模板，vector<int>是一个类型，ivec是对象名,后面是初始化。
	vector<int> ivec(10, 1);

	cout << ivec.empty() << endl; 
	cout << ivec.size() << endl;

	// 赋值
	for (vector<int>::size_type ix = 0; ix != ivec.size(); ++ix)
	{
		ivec[ix] = ix;
	}
	// 输出每个元素
	for (ix = 0; ix != ivec.size(); ++ix)
	{
		cout << ivec[ix] << ' ';
	}
	cout << endl;

	ivec.push_back(10);
	for (ix = 0; ix != ivec.size(); ++ix)
	{
		cout << ivec[ix] << ' ';
	}
	cout << "\n";

	// 用const_iterator来输出每个元素
	for (vector<int>::const_iterator iter2 = ivec.begin(); iter2 != ivec.end(); ++iter2)
	{
		cout << *iter2 << ' ';
//		*iter2 = 0; // 这是指向cosnt对象的迭代器
	}
	
	return 0;
}
