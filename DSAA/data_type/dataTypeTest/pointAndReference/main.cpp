int add(int i, int& j)
{
    return i + j;
}
typedef unsigned long       DWORD;
#include <iostream>
int main()
{
    int a = 10;
    int b = 20;
    DWORD dd = 30;
    int ee = (int)dd;
   
    int c = add(a, b);
    c = add(a, ee);
    std::cout << c << std::endl;
    return 0;
}