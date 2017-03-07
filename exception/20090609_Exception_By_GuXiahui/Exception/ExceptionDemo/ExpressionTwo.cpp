// ExpressionTwo.cpp: implementation of the ExpressionTwo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExpressionTwo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExpressionTwo::ExpressionTwo()
{

}

ExpressionTwo::~ExpressionTwo()
{

}
ExpressionTwo ExpressionTwo::operator+(const ExpressionTwo& i)
{
	printf("ExpressionTwo operator +\n");
	return *this;
}