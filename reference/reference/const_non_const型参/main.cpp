#include <iostream>
class X {
public:
    X(int); // 为整型到类型X的隐式转换提供了基础，我认为浮点到int，
            // int到浮点在各自类型的定义中都提供了这样的构造函数。
    void m1();
    void m2() const;

    friend void f1(X&); // 都是全局函数
    friend void f2(const X&);
    friend void f3(X);

private:
    int x;
};

X::X(int i)
{
    x = i;
}

void X::m1()
{
    std::cout << "X::m1()" << std::endl;
}

void X::m2() const
{
    std::cout << "X::m2()" << std::endl;
}

void f1(X& a)
{
    std::cout << "friend f1()" << std::endl;
}

void f2(const X& a)
{
    std::cout << "friend f2()" << std::endl;
}

void f3(X a)
{
    std::cout << "friend f3()" << std::endl;
}

int main()
{
    // 99.m1();     // 这个时候不会发生隐式类型转换，f2(99)是因为形参定义和初始化时发生的，
                    // const X& a = 99，f3(99)也是形参定义并初始化时
                    // 还有样的情况X a(3); X b = a + 24;这个时候应该会发生，
    // 99.m2();
    // f1(99);      // 非const引用只能绑定到与该类型同类型的对象
    f2(99);         // 这里就像做了这样一件事，定义并初始化了一个形参，const X& a = 99，
                    // 可以这样定义的理由就是
    // const引用则可以绑定到不同但相关的类型的对象或绑定到右值
    // 在这里f2的形参a关联到了一个X类型的临时变量
    // 正常的时候形参a关联到一个const X对象，这个时候它关联到一个临时变量还是局部变量呢，
    // 如果是临时变量，之后的引用又引用的谁呢
    // 如果是局部变量就能够理解了
    // 还有f2现在是绑定到一个关联类型的情况，当const引用关联到右值时，是不是也是定义
    // 一个局部变量，或者说是临时变量呢。
    f3(99);
    // f1(99);
    // 是不是因为f2(),f3()都一定不会更改实参的原因，

    X a(3);
    X b(4);
    b = a + 24;
    return 0;
}
