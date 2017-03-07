#include <iostream>
class CBook {
public:
    void print()
    {
        std::cout << "I Love China" << std::endl;
    }
    static void print() // 不能构成重载
    {
        std::cout << "I Love Japan" << std::endl;
    }
};

int main()
{
    CBook a;
    a.print();
    return 0;
}
