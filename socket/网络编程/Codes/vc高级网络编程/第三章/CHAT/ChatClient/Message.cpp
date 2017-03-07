// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatClient.h"
#include "Message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()
{
	image = 6;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");
}

CMessage::~CMessage()
{

}

void CMessage::Serialize(CArchive &ar)
{
	if (ar.IsStoring()){
		ar << type;
		ar << (WORD)m_bClose;
		ar << m_strText;
		ar << (WORD)secret;
		ar << from;
		ar << to;
		ar << (DWORD)color;
		ar << image;
	}
	else{
		WORD wd;
		DWORD dwTmp;

		ar >> type;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
		ar >> wd;
		secret = (BOOL)wd;
		ar >> from;
		ar >> to;
		ar >> dwTmp;
		color = (COLORREF)dwTmp;
		ar >> image;
	}
/*	
	m_msgList.Serialize(ar);
	fromlist.Serialize(ar);
	tolist.Serialize(ar);
	seclist.Serialize(ar);
	typelist.Serialize(ar);
	clrlist.Serialize(ar); 
*/}

void CMessage::Reset()
{
	image = 6;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");

/*	m_msgList.RemoveAll();
	fromlist.RemoveAll();
	tolist.RemoveAll();
	seclist.RemoveAll();
	clrlist.RemoveAll(); 
	typelist.RemoveAll();
*/}
