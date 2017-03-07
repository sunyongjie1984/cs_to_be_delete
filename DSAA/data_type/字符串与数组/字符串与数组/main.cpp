#include <iostream>
#include <memory>
int main()
{
	char* p = "I love China";
	char a[13];
	//a = p;
	memcpy(a, p, 13);
	std::cout << a << std::endl;
	return 0;
}