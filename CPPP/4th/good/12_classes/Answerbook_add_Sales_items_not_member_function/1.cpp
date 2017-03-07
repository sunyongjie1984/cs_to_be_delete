#include "Sales_item.h"
using std::cout;
using std::cin;
using std::endl;
// Sales_item add(const Sales_item &a, const Sales_item &b); // 应该是因为已经在类里面声明了所以就不用在这里声明了
int main()
{
	Sales_item item1(cin);
	Sales_item item2(cin);
	cout << add(item1, item2) << endl;
	return 0;
}
  // 这个函数我把它放在类里类外原来都是可以的。
Sales_item add(const Sales_item &a, const Sales_item &b)
{
	Sales_item temp;
	temp.isbn = a.isbn;
	temp.revenue = a.revenue + b.revenue;
	temp.units_sold = a.units_sold + b.units_sold;
	return temp;
}