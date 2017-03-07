#include <iostream> 
using namespace std;
long sum(int n) // Çósum(n) == 1 * 1 + 2 * 2 + ... + n * n
{
	if(n == 1)
		return 1;
	else
		return n * n + sum(n - 1);
}
int main()
{
	int i;
	cin >> i;
	cout << sum(i) << endl;
	return 0;
}