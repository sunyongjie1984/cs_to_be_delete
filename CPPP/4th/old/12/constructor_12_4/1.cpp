#include "Sales_item.h"
using namespace std; // 终于比较搞清楚了这个类的几个构造函数了。
int main()
{
//	Sales_item item1("I Love China", 1, 10); // 错
	Sales_item item; // ISBN: 空串
	Sales_item item1("I Love China"); // ISBN: I Love China
	Sales_item item2(cin); // 输入ISBN等 cin呵呵

	Sales_item *p = new Sales_item;
	cout << *p << endl;

	cout << item << endl;
	cout << item1 << endl;
	cout << item2 << endl;
	return 0;
}