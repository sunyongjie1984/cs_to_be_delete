// CalculatorAPI.h: interface for the Calculator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULATORAPI_H__4D2578E0_E87B_495D_AABF_50D4CED4B005__INCLUDED_)
#define AFX_CALCULATORAPI_H__4D2578E0_E87B_495D_AABF_50D4CED4B005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CALCULATOR_EXPORTS
#define CALCULATORAPI __declspec(dllexport)
#else
#define CALCULATORAPI __declspec(dllimport)
#endif

// Global function of add operation
extern "C" CALCULATORAPI int Add( int nLeft, int nRight );

class CALCULATORAPI Calculator  
{
public:
	Calculator();
	virtual ~Calculator();

	// Member function of add operation
	int Add( int nLeft, int nRight );
};

#endif // !defined(AFX_CALCULATORAPI_H__4D2578E0_E87B_495D_AABF_50D4CED4B005__INCLUDED_)
