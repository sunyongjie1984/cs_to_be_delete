// Allocator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyAllocator.h"
#include <vector>
#include <list>
int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	std::vector<int, MyAllocator<int> > vi;
	vi.push_back(3);
	printf( "%d", vi[0]);
	std::list<int, MyAllocator<int> > li;
	li.push_back(3);
	std::list<int, MyAllocator<int> >::iterator litor = li.begin();
	printf( "%d", *litor);
	return 0;
}

