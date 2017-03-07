#include <assert.h>
#include <iostream>
// available, musb be after including assert.h
#define NDEBUG
void func(int* p)
{
#ifndef NDEBUG
	assert(0 != p);
#endif

#ifndef NDEBUG
	std::cerr << "Error: " << __FILE__
		<< " : line " << __LINE__
		<< " compiled on " << __DATE__
		<< " at " << __TIME__ << std::endl;
#endif

	printf("hehe\n");
}

int main()
{
	func(0);
	return 0;
}
