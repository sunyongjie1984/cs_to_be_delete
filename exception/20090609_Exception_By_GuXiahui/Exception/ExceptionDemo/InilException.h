// InilException.h: interface for the InilException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INILEXCEPTION_H__9FB47727_080F_47CE_9656_9DFCA77C3C29__INCLUDED_)
#define AFX_INILEXCEPTION_H__9FB47727_080F_47CE_9656_9DFCA77C3C29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Unlucky
{
public:
	Unlucky()
	{
		throw 1;
	}
};
class InilException  
{
public:
	InilException();
	virtual ~InilException();
public:
	int* m_array;
	Unlucky m_u;
};

#endif // !defined(AFX_INILEXCEPTION_H__9FB47727_080F_47CE_9656_9DFCA77C3C29__INCLUDED_)
