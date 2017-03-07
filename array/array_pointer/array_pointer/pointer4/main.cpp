#include <iostream>
int main()
{
    int test[2][3] = { {1, 2, 3}, { 4, 5, 6 } };
    int (*p)[3];
    p = test[1];
    std::cout << *p << std::endl;
    return 0;
}    