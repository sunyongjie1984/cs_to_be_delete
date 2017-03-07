// FunctionTryBlock.h: interface for the FunctionTryBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTIONTRYBLOCK_H__F3634DAF_1C20_4E3C_ABE3_BA6F39880E50__INCLUDED_)
#define AFX_FUNCTIONTRYBLOCK_H__F3634DAF_1C20_4E3C_ABE3_BA6F39880E50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class A{
public:
	A(int i)
	{

	};
};
class B{
public:
	B()
	{

	};
};
class FunctionTryBlock :private A 
{
public:
	FunctionTryBlock();
	virtual ~FunctionTryBlock();
private:
	B m_b;
};

#endif // !defined(AFX_FUNCTIONTRYBLOCK_H__F3634DAF_1C20_4E3C_ABE3_BA6F39880E50__INCLUDED_)
