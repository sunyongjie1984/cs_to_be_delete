#include <iostream>
int main()
{
    int i = 3;
    float f = 4.5;
    std::cout << f << std::endl;
    f = static_cast<float>(i);
    std::cout << f << std::endl;
    return 0;
}
