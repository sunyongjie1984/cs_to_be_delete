#include <iostream>
class CBook {
    int a;
};
struct CBook2 {
    int a;
};
int main()
{
    std::cout << sizeof(CBook)  << std::endl;
    std::cout << sizeof(CBook2) << std::endl;
    return 0;
}
