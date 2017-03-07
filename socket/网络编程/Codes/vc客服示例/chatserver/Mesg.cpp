// Mesg.cpp : implementation file
//

#include "stdafx.h"
#include "chatserver.h"
#include "Mesg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesg

//IMPLEMENT_DYNCREATE(CMesg, CCmdTarget)

CMesg::CMesg()
{
}

CMesg::~CMesg()
{
}


//BEGIN_MESSAGE_MAP(CMesg, CCmdTarget)
	//{{AFX_MSG_MAP(CMesg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesg message handlers

void CMesg::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar<<type;
		ar<<from;
		ar<<to;
		ar<<m_str;
	}
	else
	{
		ar>>type;
		ar>>from;
		ar>>to;
		ar>>m_str;
	}
}

void CMesg::init()
{
	type=0;
	from=to=m_str=_T("");
}
