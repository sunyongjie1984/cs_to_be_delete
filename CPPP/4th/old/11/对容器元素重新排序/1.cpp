#include <iostream>
#include <string> // 例子是: the quick red fox jumps over the slow red turtle
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	vector<string> words(10);
	// 利用下标，实现循环输入
	for (vector<string>::size_type i = 0; i != words.size(); i++)
	{
		cin >> words[i];
	}
	sort(words.begin(), words.end());
	// 利用迭代器，实现循环输出
	for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	
	vector<string>::iterator end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());

    for (vector<string>::iterator iter2 = words.begin(); iter2 != words.end(); iter2++)
	{
		cout << *iter2 << " ";
	}
	return 0;
}