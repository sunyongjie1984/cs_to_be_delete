#include "Item_base.h"
class Bulk_item : public Item_base 
{
public:
	Bulk_item(const std::string& book = "", double sales_price = 0.0,
	  size_t qty = 0, double disc_rate = 0.0)
	    : Item_base(book, sales_price), min_qty(qty), discount(disc_rate) { }
	double net_price(size_t) const;
	
	// 试验你这个函数
	void Bulk_item::memfcn(const Bulk_item&, const Item_base&);
private:
	size_t min_qty;
	double discount;
};
double Bulk_item::net_price(size_t cnt) const
{
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	else
		return cnt * price;
}
/*
void Bulk_item::memfcn(const Bulk_item& d, const Item_base& b)
{
	// 1.派生类只能通过派生类对象访问基类protected成员，2.派生类对其
	// 基类类型对象的protected成员没有特殊访问权限。

	// 1.是不是可以这样理解为：访问d.price是合法，这个是不是因为d是Bulk_item的对象
	// d当然可以访问自己的数据成员了,虽然这个成员是从基类继承过来的
	// 但是我自己--d，已经通过构造函数定义了price这个成员并且赋值了
	// 而且这是在我自己的类Bulk_item中
	// 第一句话也是说：Bulk_item类通过d访问了基类的price成员。其实也是访问自自己的
	// 数据成员。注意是类访问，下面也是说在Bulk_item类中不能访问的意思吧。

	// b.price不能够访问是不是因为是在类Bulk_item中，注意一个字一个字
	// 地理解第2句话，"派生类对其基类对象（Bulk_item对b的price成员）
	// 没有特殊访问权限。

	// 感觉b.price整体上是私有的，只能是由基类的成员函数才能访问，你这样直接把它
	// 写出来一定是不行的，那么d.price为什么又可以呢？因为基类中定义，
	double ret = price;
	ret = d.price; // ok.
	ret = b.price;
}*/