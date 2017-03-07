#include <iostream>
#include <string>
using namespace std;
int main()
{
	int sum = 0;
	for (int i = 0; i != 10; ++i)
		sum += i;
	cout << "Sum from 0 to " << i  // 书中说不合法，因为i的作用域，但是却是能用，可能是i没有被写掉的原故吧
		 << " is " << sum << endl; // 看习题2_20我得到了收获
	return 0;
}