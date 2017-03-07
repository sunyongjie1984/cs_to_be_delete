#include "myException.h"

myLog winLog;

int main()
{
	int x = 1;

	try
	{
		myException* myExp = new myException(4,"this is to test!");
		throw myExp;
	}
	catch (myException* excp)
	{
		excp->response();
		delete excp;
	}

	return x;
}