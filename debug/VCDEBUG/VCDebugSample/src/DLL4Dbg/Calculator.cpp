// Calculator.cpp: implementation of the CCalculator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DLL4Dbg.h"
#include <DLL4Dbg\Calculator.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalculator::CCalculator()
{

}

CCalculator::~CCalculator()
{

}

bool CCalculator::Plus(double x, double y, double* result)
{
//	ASSERT(FALSE);
//	char* p = NULL;
//	char* p1 = NULL;
//	*p = 'c';
//	strcmp(p,p1);
	if ( NULL == result )
		return false;

	*result = x + y;
	return true;
}
