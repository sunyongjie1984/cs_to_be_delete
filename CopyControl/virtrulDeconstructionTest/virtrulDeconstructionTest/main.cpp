#include <iostream>
class CBook {
public:
    CBook()
    {
        a = 10;
        b = 100;
    }
    virtual ~CBook()
    {
        std::cout << "CBook deconstruction" << std::endl;
    }
private:
    int a;
    int b;
};

class CBookChild : public CBook {
public:
    ~CBookChild()
    {
        std::cout << "CBookChild deconstruction" << std::endl;
    }
};

int main()
{
    // CBook a; // 析构函数好像是只有两种情况会调用，1，像a这种非new出来的对象，在生命期结束时析构
    CBook* p = new CBookChild();                  // 2，这种new出来的对象，不delete不调用。
    delete p;

    // 对于一个普通函数来说，这个析构函数应该只调用一次，因为这个指针实际上是指向一个子类对象的，
    // 可是因为是析构函数，所有基类的
    // 析构函数也被调用了，用来析构基类部分，因为其实说实在的，在这个类对象构造的时候不是也从父类的
    // 构造函数开始的么!

    // CBook* q = new CBookChild(3); // 这里说明错误与拷贝构造函数有关，我现在还不明白。
    return 0;
}