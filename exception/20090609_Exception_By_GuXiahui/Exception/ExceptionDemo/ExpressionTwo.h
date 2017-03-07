// ExpressionTwo.h: interface for the ExpressionTwo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPRESSIONTWO_H__3EF346A6_52C8_4A20_A93D_35D0CE0D46B7__INCLUDED_)
#define AFX_EXPRESSIONTWO_H__3EF346A6_52C8_4A20_A93D_35D0CE0D46B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ExpressionTwo  
{
public:
	ExpressionTwo();
	virtual ~ExpressionTwo();
	ExpressionTwo operator+(const ExpressionTwo& i);
};

#endif // !defined(AFX_EXPRESSIONTWO_H__3EF346A6_52C8_4A20_A93D_35D0CE0D46B7__INCLUDED_)
