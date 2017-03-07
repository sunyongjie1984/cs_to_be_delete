// ExpressionOne.h: interface for the ExpressionOne class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPRESSIONONE_H__B2767713_C2E2_44D7_BFF8_D60CE3DC8D6E__INCLUDED_)
#define AFX_EXPRESSIONONE_H__B2767713_C2E2_44D7_BFF8_D60CE3DC8D6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ExpressionOne  
{
public:
	ExpressionOne();
	virtual ~ExpressionOne();
	ExpressionOne operator+(const ExpressionOne& i);
};

#endif // !defined(AFX_EXPRESSIONONE_H__B2767713_C2E2_44D7_BFF8_D60CE3DC8D6E__INCLUDED_)
