#include <iostream> 
//using std::cout; using std::endl;
#include <string>  // 这些东西这么多，主要还是size_t与size_type的事
#include <list>    // char*对应size_t，string对应size_type
#include <vector>
#include <cstddef>
using namespace std;
int main()
{
	// 太烦事了，终于调的差不多了，这些个例子都好好看看吧，兄弟
    string words[] = { "stately", "plump", "buck", "mulligan" };
	// 求长度

    // 看看sizeof(char*)多大
//  list<string>::size_type words_size = sizeof(words) / sizeof(char*); 
	// 看看sizeof(string)多长
	list<string>::size_type words_size = sizeof(words) / sizeof(string);  

	cout << words_size << endl;
	// 复制
	// 使用sizeof(string)的方法能够正常的求出数组元素的个数。
    list<string> words2(words, words + words_size);
	// 输出
	
	for (list<string>::size_type j = 0; j != words_size; ++j)
	{
//		cout << words2[j] << endl; // 为什么会说我的这个操作符[]没有定义呢
	}
	
	for (list<string>::iterator m = words2.begin(); m != words2.end(); m++)
	{
		cout << *m << " ";
	}
    cout << endl;

	// 下面是一个实验，看看别的什么类型可不可以
	int a[] = { 1, 3, 5, 7 };
	vector<int> b(a, a + 4);
	for (vector<int>::iterator p2 = b.begin(); p2 != b.end(); p2++)
	{
		cout << *p2 << " ";
	}
	cout << endl;
	
	// 再作一个实验 这个要强烈地与第一个例子对比！！！！！
	char *a2[] = { "ILoveChina", "YesI do" };
    size_t length = sizeof(a2) / sizeof(char*);
	vector<char*> b2(a2, a2 + length);

	for (vector<char*>::iterator p3 = b2.begin(); p3 != b2.begin() + length; p3++)
	{
		cout << *p3 << " ";
	}

    return 0;
}
