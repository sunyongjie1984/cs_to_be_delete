// n的阶乘

#include <iostream>
using namespace std;

int main()
{
    unsigned long fac(unsigned int const & n);
    unsigned int n;
    unsigned long y;
    cout << "输入一个正整数:";
    cin >> n;

    y = fac(n);
    cout << y << endl;
    return 0;
}

unsigned long fac(unsigned int const & n)
{
    unsigned long f;
    if(0 == n)
    {
        f = 1;
    }
    else
    {
        f = fac(n - 1) * n; //递归调用
    }
    return f;
}

