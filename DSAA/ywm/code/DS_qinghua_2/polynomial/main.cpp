#include <iostream>
#include "polynomial.h"

#ifdef __linux
#include <stdio.h>
#endif

int add(int i, int j)
{
    return i + j;
}

int test(int i, int j, int (*pFun)(int, int))
{
    return pFun(i, j);
}
int main()
{
    std::cout << test(3, 4, add) << std::endl;
    getchar();
    return 0;
}