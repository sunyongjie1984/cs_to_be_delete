//============================================================================
// Name        : StaticHash.cpp
// Author      : sunyj
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "static_hash.h"

int main()
{
	CHash a(10, 10);
	int n = 20;
	int m = 103;
	a.add((char*)(&n), (void*)(&m));

	void* p;
	a.get((char*)(&n), p);

	std::cout << *(static_cast<int*>(p)) << std::endl;

	return 0;
}
