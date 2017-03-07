#include <iostream>
extern int add(const int& a, const int& b);
int main()
{
    std::cout << add(3, 4) << std::endl;
    return 0;
}