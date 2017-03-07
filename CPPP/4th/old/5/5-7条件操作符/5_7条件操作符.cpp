#include <iostream>
using namespace std;
int main()
{
	int i = 10, j = 11;
	cout << (i < j ? i : j) << endl;
	cout << (i < j) ? i : j << endl;
	return 0;
}