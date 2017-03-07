#include <iostream>
#include <stdio.h>

// comma expression

int main()
{
    int a = 3;
    int b = 5;
    int c = 7;
    c = a, a * b;
    std::cout << c << std::endl;
    c = (a, a * b);
    std::cout << c << std::endl;

    getchar();
    return 0;
}