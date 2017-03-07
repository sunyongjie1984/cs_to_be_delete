// Negate.cpp
#include <iostream>
using namespace std;

class Negate
{
public:
    Negate()
    {
        std::cout << "template <class T> constructor" << std::endl;
    }
    template<class T> T operator()(T const & t) const
    {
        return -t;
    }
    ~Negate()
    {
        std::cout << "template <class T> destructor" << std::endl;
    }
};

void Callback(int n, Negate const & neg) // 传递一个函数对象
{
    n = neg(n);  // 调用重载的()操作来对n进行negate操作
    cout << n << endl;
}

int main(int argc, char * argv[])
{
    // 调用方式一
    // 临时对象是不是具有语句作用域啊，callback定义了一个引用形参
    // 绑定到了下面的这个临时对象，是不是有问题，如果这个临时对象
    // 能够坚持到callback语句结束，那么就没有问题，我可以通过给类
    // template<class T>加析构函数来了解，通过调试，发现是这样子的
    // 结论就是可以定义一个形参绑定到一个临时对象的实参
    Callback(5, Negate());

    // 调用方式二
    //Negate neg;
    //cout << neg(9.99999) << endl;
    //cout << neg(__int32(39999999)) << endl;

    return 0;
}