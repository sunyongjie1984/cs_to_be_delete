#include <iostream>
#include <math.h>
double f(double x)
{
	return 2 * x + 1;
}

double root(double (*f)(double), double a, double b, double e)
{
	double middle = (a + b) / 2;
	while (f(middle) != 0 && fabs(b - 1) > e)
	{
		if(f(a) * f(middle) < 0)
		{
			b = middle;
		}
		else 
		{
			a = middle;
		}
		middle = (a + b) / 2;
	}
	return middle;
}

int main()
{
	std::cout << root(f, -20, 20, 0.001);
	return 0;
}

	