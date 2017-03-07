#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item a;
    Sales_item b;
    // 主要学习return by value值返回，在全局函数
    // Sales_item operator+(Sales_item const &, Sales_item const &)
    // 中，在return语句中，编译器1，首先调用拷贝构造函数复制对象ret，用于返回ret的复本
    // 然后，因为语句块Sales_item operator+(Sales_item const &, Sales_item const &)作用域
    // 的结束，2，要调用ret的析构函数，3，对于返回的ret的复本对象，这是一个临时对象，
    // 在使用这个对象作为全局函数ostream& operator<<(ostream &, Sales_item const &)的右
    // 操作数后，要调用这个临时对象的析构函数
    std::cout << a + b << std::endl;

    return 0;
}

//Sales_item()                    // a的构造函数
//Sales_item()                    // b的构造函数
//Sales_item(Sales_item const &)  // Sales_item ret(lhs)
//Sales_item(Sales_item const &)  // 临时变量（ret的复本）的构造函数
//2 ~Sales_item()                 // ret的析构函数
//0       0       0               // std::cout的打印
//3 ~Sales_item()                 // 临时变量（ret的复本）的析构函数
//1 ~Sales_item()                 // b的析构函数
//0 ~Sales_item()                 // a的析构函数