#include "StdAfx.h"
#include "ExpressionTwo.h"

ExpressionTwo::ExpressionTwo(void)
{
}

ExpressionTwo::~ExpressionTwo(void)
{
}
ExpressionTwo ExpressionTwo::operator+(const ExpressionTwo& i)
{
	printf("ExpressionTwo operator +\n");
	return *this;
}