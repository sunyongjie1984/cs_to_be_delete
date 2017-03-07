/* 15.3.1 派生类到基类的转换
如果有一个派生类对象，
1.则可以使用它的地址对基类对象的指针进行赋值或初始化。
2.也可以使用派生类对象或引用初始化基类类型的引用。
3.严格说来，对对象没有类似的转换，编译器不会将派生类类型对象转换为基类类型对象。
4.但是一般可以使用派生类型对象对基类对象进行赋值或初始化。
 */
#include <iostream>
#include "Bulk_item.h"
using namespace std;

void print_total(ostream & os, const Item_base & item, size_t n)
{
    os << "ISBN " << item.book() << "\tnumber sold: " << n << "\ttotal price: " 
        << item.net_price(n) << endl;
}

int main()
{
    Bulk_item a("sunyongjie", 20, 10, 0.1); // isbn sunyongjie, price 20, min_qty 10
                                            // , discount 0.9
    Bulk_item b("wangjie", 20, 10, 0.2);
    Item_base * p = &a; // 初始化
    p->display_datamember();

    p = &b;             // 赋值
    p->display_datamember();

    std::cout << "............................\n" << std::endl;

    Item_base c("sunyongjie2", 20);
    Item_base & q = c;  // 初始化时没有给基类引用一个子类的对象或引用，在后来通过赋值操作
                        // 给这个引用以子类对象或引用是不能够触发动态绑定的
                        // huge mistake, the following statement means reassign c with a, not
                        // reference q binds to another object, reference for its whole life binds to one object!!!!
    q.display_datamember();
    q = a;              // q is another name of object c, this assignment assign a to c
    q.display_datamember();

    q = b;
    q.display_datamember();
    std::cout << "............................\n" << std::endl;

    Item_base & m = a;
    m.display_datamember(); // 动态绑定触发

    Bulk_item & d = b;
    Item_base & e = d;
    e.display_datamember(); // 动态绑定触发
    std::cout << "............................\n" << std::endl;

    Item_base f = a;        // 不知道这里为什么编译器连一个警告也不给。
    f.display_datamember(); // 用派生类对象初始化基类对象怎么可以呢(this page line 6)，我用F11调试居然没有显示
                            // 走没有构造函数，调试进不去的原因是不是因为虽然是一个定义，但是并没有走构造函数，而是
                            // 直接通过截断子类对象的子类部分，然后去初始化了基类的对象f，很微秒
    print_total(cout, a, 10);
    print_total(cout, f, 10);
    return 0;
}
