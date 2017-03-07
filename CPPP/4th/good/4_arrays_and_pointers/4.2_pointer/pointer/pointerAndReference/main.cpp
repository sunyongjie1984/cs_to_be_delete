#include <iostream>
void set(char*);
int main()
{
	char *p = "I Love China!" ;
	set(p);
	std::cout << p << std::endl; // "You Love China!" ;
	return 0;
}
void set (char* p)
{
	std::cout << p << std::endl; // "I Love China"
	p = "You Love China!" ;
	std::cout << p << std::endl; // "You Love China!" ;
}
