#include <iostream> 
using namespace std;
int main() // 没有发现语句作用域，i在for外面还是可以用啊
{
	int x = 0;
	for (int i = 0; i < 10; i++)
	{
		cout << i << endl;
	}
    cout << x << endl;
//	i++;
	cout << i + 200 << endl;
	return 0;
}