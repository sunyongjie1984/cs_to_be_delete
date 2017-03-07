// SenderDoc.cpp : implementation of the CSenderDoc class
//

#include "stdafx.h"
#include "Sender.h"

#include "SenderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSenderDoc

IMPLEMENT_DYNCREATE(CSenderDoc, CDocument)

BEGIN_MESSAGE_MAP(CSenderDoc, CDocument)
	//{{AFX_MSG_MAP(CSenderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSenderDoc construction/destruction

CSenderDoc::CSenderDoc()
{
	// TODO: add one-time construction code here

}

CSenderDoc::~CSenderDoc()
{
}

BOOL CSenderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSenderDoc serialization

void CSenderDoc::Serialize(CArchive& ar)
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
// CSenderDoc diagnostics

#ifdef _DEBUG
void CSenderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSenderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSenderDoc commands
