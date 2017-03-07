#include "Bulk_item.h"
int main()
{
    Bulk_item a("sunyongjie", 20, 10, 0.9); // isbn sunyongjie, price 20, min_qty 10
    // , discount 0.9
    Item_base* p = &a; // 指向父类对象的指针被赋值为子类对象的地址

    a.display_datamember();  // 没有什么说的，正常调用自己的对象
    p->display_datamember(); // 动态绑定发生，调用子类的函数
    p->Item_base::display_datamember(); // 所谓覆盖虚函数调用机制
    getchar();
    return 0;
}
