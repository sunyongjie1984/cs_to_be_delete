#include "Bulk_item.h"
/*
void memfcn(const Bulk_item& d, const Item_base& b)
{
	double ret;
	ret = d.price; // 函数放在此处则两个price都不可以访问，原因是这个
	ret = b.price; // 全局函数不可以访问类中的protected,与在类中只有
}*/                // 只有b.price不能访问相对比，孙永杰你能懂点么？
int main()
{
	return 0;
}