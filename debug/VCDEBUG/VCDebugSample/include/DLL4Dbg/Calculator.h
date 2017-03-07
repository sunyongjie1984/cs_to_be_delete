// Calculator.h: interface for the CCalculator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULATOR_H__01BCDF16_B86D_4854_B55D_5FEF804EAB0E__INCLUDED_)
#define AFX_CALCULATOR_H__01BCDF16_B86D_4854_B55D_5FEF804EAB0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef EXPORT_CALCULATOR
#define CALCULATOR_DLL __declspec(dllexport)
#else
#define CALCULATOR_DLL __declspec(dllimport)
#endif

class CALCULATOR_DLL CCalculator
{
public:
	bool Plus( double x, double y, double* result );
	CCalculator();
	virtual ~CCalculator();

};

#endif // !defined(AFX_CALCULATOR_H__01BCDF16_B86D_4854_B55D_5FEF804EAB0E__INCLUDED_)
