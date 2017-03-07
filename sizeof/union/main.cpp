#include <iostream>
union mm{   
    char   a;
    int   b[5];
    double   c;
    int   d[3];
};

int main()
{
    std::cout << sizeof(mm) << std::endl;
    return 0;
}
