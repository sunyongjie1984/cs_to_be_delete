// Allocator.cpp : Defines the entry point for the console application.
//

 #include "stdafx.h"
// #include "MyAllocator.h"
#include "DefaultAllocator.h"
#include <vector>
#include <list>
class Test
{
public:
		int nArray[100];
public:
	Test()
	{
		for( int j = 0; j < 100; j++)
		{
			nArray[j] = j;
		}
	}
	Test operator=(const Test& Ref)
	{
		for( int j = 0; j < 100; j++)
		{
			this->nArray[j] = Ref.nArray[j];
		}
		return *this;
	}
	Test(const Test& Ref)
	{
		for( int j = 0; j < 100; j++)
		{
			this->nArray[j] = Ref.nArray[j];
		}
	}
};
int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	Test test;
	//std::vector<int, MyAllocator<int> > vi;
	std::vector<Test, DefaultAllocator<Test> > vi;
	
	vi.push_back(test);

	printf( "%d\n", vi[0]);
 	std::list<int, DefaultAllocator<int> > li;
 	li.push_back(3);
 	std::list<int, DefaultAllocator<int> >::iterator litor = li.begin();
 	printf( "%d\n", *litor);
	li.erase(litor);
	return 0;
}

