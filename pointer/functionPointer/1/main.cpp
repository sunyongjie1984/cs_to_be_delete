#include <iostream>
typedef int (*ONLOADFUN)(int i, int j);
int (*add4)(int i, int j);
int add3(int a, int b)
{
    return a + b + 3;
}
int main()
{
    ONLOADFUN add4;
    add4 = add3;
    std::cout << add4(4, 5) << std::endl;

    ONLOADFUN add5;
    add5 = ONLOADFUN(add3);
    std::cout << add5(4, 5) << std::endl;

    ONLOADFUN add6;
    add6 = (ONLOADFUN)add3;
    std::cout << add6(4, 5) << std::endl;
    return 0;
}
