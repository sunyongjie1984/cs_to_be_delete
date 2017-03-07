#include <iostream>
using std::cout;
using std::endl;
class classf
{
public:
	classf() 
	{
	}
	double operator()(double x)
	{
		return 2 * x;
	}
};

double sum2(classf f, int n, int m)
{
	double result = 0;
	for (int i = n; i <= m; i++)
	{
		result += f(i);
	}
	return result;
}

int main()
{
	class cf;
	cout << sum2(classf(), 2, 3) << endl;
//	cout << sum2(cf, 2, 3) << endl; // 为什么错啊，书中22页写着的啊！

	return 0;
}
