#include <iostream>
#include <stdlib.h>

#include "stack.h"
using namespace std;
//Print integer num in base B
void MultibaseOutput(long num, int B)
{
	Stack<int, 10> s;

	do
	{
		s.Push( num % B);
		num /= B;
	} while (num != 0);

	while ( !s.StackEmpty())
		cout << s.Pop();
}

void main(void)
{
	long num;
	int B;

	for(int i = 0; i<3; i++)
	{
		cout << "Enter number and base (2 - 9):" << endl;
		cin >> num >> B;
		cout << num << " base " << B << " is ";
		MultibaseOutput(num, B);
		cout << endl;
	}
}

