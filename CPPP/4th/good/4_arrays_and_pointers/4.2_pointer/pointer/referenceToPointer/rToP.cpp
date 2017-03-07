#include <iostream>
void set(char*&);
int main()
{
	char *p = "I Love China!";
	set(p);
	std::cout << p << std::endl;
	return 0;
}
void set (char*& p)
{
	p = "You love China!";
}
