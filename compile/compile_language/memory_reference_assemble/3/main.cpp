int& add2(int a, int b)
{
    int c = a + b;
    return c; // 这句语句会给警告。
}

int add(int a, int b)
{
    int c = a + b;
    return c; // 这句就不会给警告。
}

#include <iostream>
int main()
{
    int i = 10;
    int j = 20;
    int m = add(i, j);
    int n = add2(i, j);
    std::cout << m << " " << n << std::endl;
    return 0;
}       