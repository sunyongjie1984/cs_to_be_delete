// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
#define AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessage : public CObject  
{
public:
	void Serialize(CArchive& ar);
	CMessage();
	virtual ~CMessage();
public:
	void Reset();
	CString m_strText;
	CString from;
	CString to;

	COLORREF color;
	BOOL secret;
	BOOL m_bClose;
	int type;
	WORD image;
};

#endif // !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
