#include <iostream>
#include <stdint.h>
int main()
{
    uint64_t a = 10;
    uint32_t d = 10;
    int32_t  b = -10;
    uint32_t c = 1;
    std::cout << b * c << std::endl;

    a += b * c;
    std::cout << a << std::endl;
    a = 10;
    a += b * static_cast<int32_t>(c);
    std::cout << a << std::endl;
    std::cout << "haha " << b * static_cast<int32_t>(c) << std::endl;
    std::cout << "hehe " << b * c << std::endl;
    d += b * c;
    std::cout << d << std::endl;
    std::cout << b * c << std::endl;



    return 0;
}
