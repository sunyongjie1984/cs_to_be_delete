// chatDoc.cpp : implementation of the CChatDoc class
//

#include "stdafx.h"
#include "chat.h"

#include "chatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatDoc

IMPLEMENT_DYNCREATE(CChatDoc, CDocument)

BEGIN_MESSAGE_MAP(CChatDoc, CDocument)
	//{{AFX_MSG_MAP(CChatDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDoc construction/destruction

CChatDoc::CChatDoc()
{
	// TODO: add one-time construction code here

}

CChatDoc::~CChatDoc()
{
}

BOOL CChatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChatDoc serialization

void CChatDoc::Serialize(CArchive& ar)
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
// CChatDoc diagnostics

#ifdef _DEBUG
void CChatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatDoc commands
