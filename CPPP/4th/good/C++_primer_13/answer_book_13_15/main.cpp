#include "Sales_item.h"

void fcn(const Sales_item* trans, Sales_item accum)
{
	Sales_item item1(*trans), item2(accum);
	if (!item1.same_isbn(item2))
	{
		return;
	}
	if (item1.avg_price() <= 99)
	{
		return;
	}
	else if (item2.avg_price() <= 99)
	{
		return;
	}
}

int main()
{
	int a = 3;
	Sales_item a;
	Sales_item b;
	fcn(&a, b);
	return 0;
}