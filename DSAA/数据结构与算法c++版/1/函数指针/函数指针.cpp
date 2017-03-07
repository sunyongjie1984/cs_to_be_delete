#include <iostream> // º¯ÊıÖ¸Õëg
double f(double x)
{
	return 2 * x;
}

double sum(double (*g)(double), int n, int m)
{
	double result = 0;
	for (int i = n; i <= m; i++)
	{
		result += g(i);
	}
	return result;
}

int main()
{
	std::cout << sum(f, 1, 3);
	return 0;
}

	