// StackDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyStack.h"


#include "SimpleStack.h"
#include "SimpleStack.cpp"

int main(int argc, char* argv[])
{
	SimpleStack<int> ss;
	ss.Push(1);
	
	printf("Simple stack %d!\n", ss.Pop());
	MyStack<int> ms;
	ms.Push(1);
	printf("My stack %d!\n", ms.Top());
	return 0;
}

