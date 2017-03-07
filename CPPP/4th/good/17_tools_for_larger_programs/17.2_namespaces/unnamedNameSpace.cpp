#include <iostream>

// extern from other file
extern int test;  // ok
// extern int test2; // error, test2 is local in file test.cpp
// extern int test3; // error, test3 is local in file test.cpp

// global variable
int a = 30;

// the old way of limit a variable local file
static int b = 40;

// unnamed namespace,
// c++ way of limiting a variable local file
namespace
{
	int c = 50;
}

int main()
{
	std::cout << a << " " << b << " " << c << std::endl;
	std::cout << test << std::endl;
	return 0;
}
