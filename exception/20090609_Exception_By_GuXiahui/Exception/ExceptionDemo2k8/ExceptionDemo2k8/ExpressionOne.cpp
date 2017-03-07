#include "StdAfx.h"
#include "ExpressionOne.h"

ExpressionOne::ExpressionOne(void)
{
}

ExpressionOne::~ExpressionOne(void)
{
}
ExpressionOne ExpressionOne::operator+(const ExpressionOne& i)
{	
	printf("ExpressionOne operator +\n");
	return *this;
}