#include "si.h"

int main()
{
    SmallInt si(100);
    SmallInt si2(256);
    std::cout << si.Get_Value()  << std::endl;
    std::cout << si2.Get_Value() << std::endl;
    return 0;
}
