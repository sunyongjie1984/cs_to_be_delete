#include "example.h"
int main()
{
    char * p = "1234567"; // 这种不是自己new出来的字符串的，赋值什么的，比较随意，编译器帮我析构，
                          // 类中的情况好像只有用memcpy这样的函数才能更改
    p = "american";       // char*对象的值。p可以理解为一个const char*指针，指向一个字符串，
                          // 这个字符串的内容不可以更改
                          // 也可以理解为一个字符串常量类型的对象。   
    std::cout << p << std::endl;

    CExample a;
    a.Init(20);

    CExample b = a;
    CExample c(a); // 这两个语句的意思完全一样，都是调用拷贝构造函数构造b和c。   
                   // 这种类中包含指针的类，如果没有拷贝构造函数这句话就会出错，调试中可以发现a的pBuffer与
                   // b的pBuffer指向同一块内存
                   // 此时函数结束时，先析构b，可以成功，析构a时，由于去delete同一块内存而报错;

    a.SetBuffer(p);
    // p = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"; // strlen(p) > 20.
    // a.SetTooLongBuffer(p); // 经调试发现这样做析构时delete会出错，很可能是析构时会跟据你new出来多少来析构多少内存。

    CExample d; 
    d = a; // 1.这是一个赋值操作，如果类没有定义重载赋值操作符，编译器会自动调用缺省的赋值操作符，但是由于
           // 这是一个有指针成员的类，
           // 又会在析构的时候，析构两次同一块内存。如果上面的代码没有注释掉，那么编译器会析构d，c，b，a这个顺序，
           // 在析构a时报错。 
           // 2.缺省的赋值操作只是复制相应的成员变量值，旧的值会被丢弃，旧的对象的指针成员变量所指向的new
           // 出来的对象将不会被delete，造成内存泄露。
           // 3.新生成的对象的指针变量指向给你赋值的对象的指针变量指向同一对象，而不是重新生成了指针变量指向的对象，
           // 也就是1中的析构同一位置产生的原因。所有赋值操作符的重载有两个工作，第一析构被赋值对象new出来的资源，
           // 第二是将给你赋值的对象的全部
           // 内容复制过来，包括指针成员指向的对象的内容的重新生成。
    // b = a;
    // a.PrintBuffer();
    // b.PrintBuffer();
    return 0;
}
