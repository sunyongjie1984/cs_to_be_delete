#include <iostream>

class C {
public:
    // int & getRef() const // 一定不对，总是错的
    // int const & getRef() const // 后一个const说明这个成员函数不会修改成员，前一个const表示接受
                                  // 数据成员n不会因为被一个引用绑定而改变
    int & getRef() 
    {
        return n;
    }
    int getN() const
    {
        return n;
    }

private:
    int n;
};

int main()
{
    C c;
    // int k = c.getN(); // 看好这两句话的不同。呵呵。
    int& k = c.getRef();
    k = 7;
    std::cout << c.getN() << std::endl;
    return 0;
}