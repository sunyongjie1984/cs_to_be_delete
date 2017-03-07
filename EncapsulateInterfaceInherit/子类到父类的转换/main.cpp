#include <iostream>

class father {
public:
    //father() { i = 10; j = 20; } // 这样不好
    father() : i(10), j(20) { }     // good
    virtual void print() const
    {
        std::cout << i << " " << j;
    }
private:
    int i;
    int j;
};

class son: public father {
public:
    //son() { m = 30; } // 这样不好
    son() : m(30) {}    // 这样可能与下面这行一样
    //son() : father(), m(30) {}
    void print() const
    {
        father::print(); // 不知道这种作法好不好？
        std::cout << " " << m;
    }
private:
    int m;
};

int main()
{
    father* p = new son;
    p->print(); // 动态绑定

    son aa;
    father const & bb = aa;
    bb.print(); // 动态绑定
    std::cout << std::endl;

    son a;
    father b = a; // 类型转换，可能会截断
    b.print();
    std::cout << std::endl;

    return 0;
}
