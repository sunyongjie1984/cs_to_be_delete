#include <iostream>
using namespace std;
int main()
{
	int sum = 0, value;
	while (cin >> value)
	{
		sum += value;
	}
	cout << "Sum is: " << sum << endl;
	return 0;
}