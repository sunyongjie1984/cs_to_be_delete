#include "Sales_item.h"
using namespace std;
int main()
{
	Sales_item item1;
	cin >> item1; // 这两个函数完全一样了，就是一个形像用的是操作符重载
//	read(cin, item1); // 这回我好好地体会了一下子，操作符重载；
	cout << item1 << endl;
	return 0;
}