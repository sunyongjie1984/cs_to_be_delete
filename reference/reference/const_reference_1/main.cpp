#include <iostream>
int main()
{
    int i = 30;
    int const & re = i;

    i += re;
    return 0;
}