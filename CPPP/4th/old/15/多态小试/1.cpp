#include <iostream>
#include "Bulk_item.h"
using std::cout;
using std::endl;
int main()
{
	Item_base *p;
	Bulk_item b("sunyongjie", 10, 5, 0.1);
	p = &b;
	double i = p->net_price(10); // 小实验成功了
	cout << i << endl;
	return 0;
}