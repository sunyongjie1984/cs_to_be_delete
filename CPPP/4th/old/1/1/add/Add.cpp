#include <iostream>

/* Simple main function: Read two numbers and write their sum */
int main()
{
	// prompt user to enter two numbers
	std::cout << "Enter two numbers:" << std::endl; 

	int v1, v2;
	std::cin >> v1 >> v2;   

	std::cout << "The sum of " << v1 << " and " << v2
	          << " is " << v1 + v2 << std::endl;

	return 0;
}

