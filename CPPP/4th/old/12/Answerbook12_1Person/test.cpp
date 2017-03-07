#include <iostream>
using namespace std;
#include "Person.h"
int main()
{
//	Person item1; // 这句话不合法，因为不能找到匹配的构造函数
	Person item1(string, string); // 这句话是合法的，为什么?
//	Person item2(string1, string); // 这句话不合法，为什么？
	Person item3("sunyongjie", "China"); 
	string s = item3.getAddress(); 
	cout << s << endl;

//	item1.address = "ddd"; // 不能访问
//	cout << item1 << endl; // 这个是因为没有进行重载么？应该是吧。
	return 0;
}