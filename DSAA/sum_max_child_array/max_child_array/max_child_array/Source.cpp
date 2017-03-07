#include <iostream>
#include <stdio.h>

int my_sum(int const * p, int const n, int & begin, int & end)
{
    int max;
    int sum;
    int max_all = p[0];
    unsigned int b = 0;
    unsigned int e = 0;

    for (int i = 0; i < n; ++i)
    {
        sum = 0;
        max = p[i];
        for (int j = i; j < n; ++j)
        {
            sum += p[j];
            if (sum > max)
            {
                max   = sum;
                b = i;
                e = j;
            }
        }
        if (max > max_all)
        {
            max_all = max;
            begin = b;
            end   = e;
        }
    }
    return max_all;
}

int main()
{
    int a[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
    int i = 0;
    int j = 0;
    std::cout << my_sum(a, sizeof(a)/ sizeof(int), i, j) << std::endl;
    for (int m = i; m < j; m++)
    {
        std::cout << a[m] << " ";
    }
    std::cout << std::endl;
    getchar();
    return 0;
}
