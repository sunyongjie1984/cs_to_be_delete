// ExceptionDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include "Uncaught_exception.h"
#include "ExpressionOne.h"
#include "ExpressionTwo.h"
#include "InilException.h"
class MyBaseException:public exception{
public:
	MyBaseException()
		:exception("MyBaseException")
	{};
	virtual void test(){
		printf("Catch MyBaseException\n");
	};
	virtual ~MyBaseException(){};
	
};
class MyException: public MyBaseException{
public:
	MyException()
	{};
	virtual void test(){
		printf("Catch MyException\n");
	};
	virtual ~MyException(){};
	
};
void FuncPointer()
{
	try
	{

		MyException e;
		throw e;
	}
	catch (MyBaseException e)
	{
		e.test();
	}
}

static void atExitFunc(void)
{
	printf("atexit\n");
}
void Funcerrno()
{
	errno = 0;
	if (NULL == fopen("d:\\1.txt", "rb"))
	{
		printf("%d\n", errno);
	}
	else
	{
		printf("%d\n", errno);
	}

}
void FuncCaughtException()
{
	try{
		Uncaught_exception a;
		throw 2;
	}
	catch(...){

	}
}
void FuncExprOrder(ExpressionOne one, ExpressionTwo two)
{

}
void FuncInitException()
{
	try{
	InilException q;
	}
	catch(...)
	{

	}
}

int main(int argc, char* argv[])
{
	//FuncPointer();
	//atexit(atExitFunc);
	//exit(EXIT_SUCCESS);
	//Funcerrno();
	//FuncCaughtException();
// 	ExpressionOne one;
// 	ExpressionTwo two;
// 	FuncExprOrder(one + one + one+ one + one+ one + one+ one + one+ one + one+ one + one+ one + one+ one + one, 
// 		two + two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two+ two + two);

	FuncInitException();
	return 0;
}

