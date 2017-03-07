// ExpressionOne.cpp: implementation of the ExpressionOne class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExpressionOne.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExpressionOne::ExpressionOne()
{

}

ExpressionOne::~ExpressionOne()
{

}
ExpressionOne ExpressionOne::operator+(const ExpressionOne& i)
{	
	printf("ExpressionOne operator +\n");
	return *this;
}