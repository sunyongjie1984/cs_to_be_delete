#include <iostream>
#include <string>
using namespace std;
void reset(int *ip)
// void reset(const int *ip)
{
	*ip = 0;
	ip = 0;
}
int main()
{
	int i = 42;
	int *p = &i;
	cout << "i: " << *p << endl;
	reset(p);
	cout << "i: " << *p << endl;
	return 0;
}