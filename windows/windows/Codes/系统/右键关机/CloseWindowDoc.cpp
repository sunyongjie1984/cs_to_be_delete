// CloseWindowDoc.cpp : implementation of the CCloseWindowDoc class
//

#include "stdafx.h"
#include "CloseWindow.h"

#include "CloseWindowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowDoc

IMPLEMENT_DYNCREATE(CCloseWindowDoc, CDocument)

BEGIN_MESSAGE_MAP(CCloseWindowDoc, CDocument)
	//{{AFX_MSG_MAP(CCloseWindowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowDoc construction/destruction

CCloseWindowDoc::CCloseWindowDoc()
{
	// TODO: add one-time construction code here

}

CCloseWindowDoc::~CCloseWindowDoc()
{
}

BOOL CCloseWindowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCloseWindowDoc serialization

void CCloseWindowDoc::Serialize(CArchive& ar)
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
// CCloseWindowDoc diagnostics

#ifdef _DEBUG
void CCloseWindowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCloseWindowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowDoc commands
