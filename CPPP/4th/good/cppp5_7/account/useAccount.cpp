#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include "Account.h"

int main()
{
	Account a1("bem", 42);
	cout << a1.balance() << endl;
	a1.calculate();
	cout << a1.balance() << endl;

    std::cin.get();
	return 0;
}
