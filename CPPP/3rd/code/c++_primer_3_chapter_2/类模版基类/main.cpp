#include "CArrayRC.h"
int main()
{
	CArrayRC<int> a;
	std::cout << a << std::endl;

	CArrayRC<int> b(10);
	std::cout << b << std::endl;

	int arr[5] = { 2, 4, 6, 10, 7};
	CArrayRC<int> c(arr, 5);
	std::cout << c << std::endl;
	std::cout << c[3] << std::endl;
	return 0;
}