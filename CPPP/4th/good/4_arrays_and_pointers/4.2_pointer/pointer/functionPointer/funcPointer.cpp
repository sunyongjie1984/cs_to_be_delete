#include <iostream>

double f(double x)
{
    return 2 * x;
}

double sum(double (*g)(double), int n)
{
    double result = g(n);
    return result;
}

int main()
{
    std::cout << sum(f, 3) << std::endl;

    double (*p_func)(double) = f;

    std::cout << p_func(2.7) << std::endl;
    return 0;
}
