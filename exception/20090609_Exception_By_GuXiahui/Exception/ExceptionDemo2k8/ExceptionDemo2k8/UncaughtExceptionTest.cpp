#include "StdAfx.h"
#include "UncaughtExceptionTest.h"
#include <exception>
UncaughtExceptionTest::UncaughtExceptionTest(void)
{
}

UncaughtExceptionTest::~UncaughtExceptionTest(void)
{

	//throw 1;
	try
	{
		close();
	}
	catch(...)
	{

	}

}
void UncaughtExceptionTest::close()
{
	throw 1;
}