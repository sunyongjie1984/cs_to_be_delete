// TestAllocDoc.cpp : implementation of the CTestAllocDoc class
//

#include "stdafx.h"
#include "TestAlloc.h"

#include "TestAllocDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAllocDoc

IMPLEMENT_DYNCREATE(CTestAllocDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestAllocDoc, CDocument)
	//{{AFX_MSG_MAP(CTestAllocDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAllocDoc construction/destruction

CTestAllocDoc::CTestAllocDoc()
{
	// TODO: add one-time construction code here

}

CTestAllocDoc::~CTestAllocDoc()
{
}

BOOL CTestAllocDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestAllocDoc serialization

void CTestAllocDoc::Serialize(CArchive& ar)
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
// CTestAllocDoc diagnostics

#ifdef _DEBUG
void CTestAllocDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestAllocDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestAllocDoc commands
