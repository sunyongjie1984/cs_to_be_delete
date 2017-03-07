#include <iostream>
#include "myException.h"

void func()
{
    try
    {
        throw my_exception("haha", "yongjisu", "A lan");
    }
    catch(my_exception & e)
    {
        std::cout << e.right << std::endl;
        e.right = "wang jie";
        throw; // ÖØÐÂÅ×³ö
    }
}

int main()
{
    try
    {
        func();
    }
    catch (my_exception const & e)
    {
        std::cout << e.right << std::endl;
        std::cout << "exception catch in main" << std::endl;
    }
    return 0;
}
