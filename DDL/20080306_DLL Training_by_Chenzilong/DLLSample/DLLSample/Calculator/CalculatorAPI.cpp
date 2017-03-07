// Calculator.cpp: implementation of the Calculator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorAPI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Calculator::Calculator()
{

}

Calculator::~Calculator()
{

}

int Calculator::Add( int nLeft, int nRight )
{
	return nLeft + nRight;	
}

int Add( int nLeft, int nRight )
{
	return nLeft + nRight;
}