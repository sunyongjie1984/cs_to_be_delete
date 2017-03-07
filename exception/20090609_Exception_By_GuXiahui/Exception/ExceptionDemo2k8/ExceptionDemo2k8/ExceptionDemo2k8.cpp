// ExceptionDemo2k8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UncaughtExceptionTest.h"
#include "TestFunctionTryBlock.h"
#include "ExpressionOne.h"
#include "ExpressionTwo.h"
void FuncTestUncaughtException()
{
	try{
		UncaughtExceptionTest a;
		throw 1;
	}
	catch(...)
	{

	}
	
}
void FuncTestFunctionTryBlock()
{
	TestFunctionTryBlock a;
}
void FuncExprOrder(ExpressionOne one, ExpressionTwo two)
{

}
int _tmain(int argc, _TCHAR* argv[])
{
	//FuncTestUncaughtException();
	try{
	FuncTestFunctionTryBlock();
	}
	catch(double d)
	{

	}catch(int i)
	{

	}
	//ExpressionOne one;
	//ExpressionTwo two;
	//FuncExprOrder(one + one + one+ one + one+ one + one+ one + one+ one + one+ one + one+ one + one+ one + one, 
	//	two + two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two);

	return 0;
}

