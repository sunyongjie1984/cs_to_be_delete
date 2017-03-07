#include <iostream>
#include "base.h"
#include "derive.h"
int main()
{
    c_base a;
    a.apple();
    a.orange();
    std::cout << std::endl;

    c_derive b;
    b.apple();
    b.orange();
    std::cout << std::endl;

    c_derive c;
    c_base* p = &c;
    p->apple();
    p->orange();

    return 0;
}
