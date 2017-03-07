#include <string>
#include <iostream>
int a = 20; // 定义并初始化，因为是全局变量，所以初始化为0
int main()
{
    int c; // 定义不初始化，因为这是局部变量且是内置类型
    std::string ss; // 定义并初始化，因为是自定义类型，而且有默认构造函数，
    // 如果没有默认构造编译不能通过。

    // 这两个都是定义，并且初始化
    // 复制初始化，c语言的方法
    int a = 10;   

    // 是不是应该先调用一个接受c风格字符串的构造函数生成临时的string对象
    // 然后调用拷贝构造函数
    std::string s = "ILoveChina"; 

    // 这两个都是定义，并且初始化
    // 直接初始化
    int b(10);                    // 面向对象的c++的方法
    std::string s2("IloveChina"); // 接受c风格字符串的拷贝拷贝构造函数

    return 0;
}