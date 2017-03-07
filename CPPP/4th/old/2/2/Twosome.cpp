#include <iostream>
int main() 
{
	std::cout << "two" // ok to break long literal across lines
                     "some" << std::endl;
	return 0;
}

