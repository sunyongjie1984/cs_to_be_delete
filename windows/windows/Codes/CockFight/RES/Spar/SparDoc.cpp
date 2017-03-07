// SparDoc.cpp : implementation of the CSparDoc class
//

#include "stdafx.h"
#include "Spar.h"

#include "SparDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSparDoc

IMPLEMENT_DYNCREATE(CSparDoc, CDocument)

BEGIN_MESSAGE_MAP(CSparDoc, CDocument)
	//{{AFX_MSG_MAP(CSparDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSparDoc construction/destruction

CSparDoc::CSparDoc()
{
	// TODO: add one-time construction code here

}

CSparDoc::~CSparDoc()
{
}

BOOL CSparDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSparDoc serialization

void CSparDoc::Serialize(CArchive& ar)
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
// CSparDoc diagnostics

#ifdef _DEBUG
void CSparDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSparDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSparDoc commands
