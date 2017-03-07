// chatserverDoc.cpp : implementation of the CChatserverDoc class
//

#include "stdafx.h"
#include "chatserver.h"

#include "chatserverDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatserverDoc

IMPLEMENT_DYNCREATE(CChatserverDoc, CDocument)

BEGIN_MESSAGE_MAP(CChatserverDoc, CDocument)
	//{{AFX_MSG_MAP(CChatserverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatserverDoc construction/destruction

CChatserverDoc::CChatserverDoc()
{
	// TODO: add one-time construction code here

}

CChatserverDoc::~CChatserverDoc()
{
}

BOOL CChatserverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChatserverDoc serialization

void CChatserverDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChatserverDoc diagnostics

#ifdef _DEBUG
void CChatserverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChatserverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatserverDoc commands
