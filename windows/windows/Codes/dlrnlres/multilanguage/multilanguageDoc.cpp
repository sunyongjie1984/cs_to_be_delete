// multilanguageDoc.cpp : implementation of the CMultilanguageDoc class
//

#include "stdafx.h"
#include "multilanguage.h"

#include "multilanguageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageDoc

IMPLEMENT_DYNCREATE(CMultilanguageDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultilanguageDoc, CDocument)
	//{{AFX_MSG_MAP(CMultilanguageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageDoc construction/destruction

CMultilanguageDoc::CMultilanguageDoc()
{
	// TODO: add one-time construction code here

}

CMultilanguageDoc::~CMultilanguageDoc()
{
}

BOOL CMultilanguageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultilanguageDoc serialization

void CMultilanguageDoc::Serialize(CArchive& ar)
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
// CMultilanguageDoc diagnostics

#ifdef _DEBUG
void CMultilanguageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultilanguageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageDoc commands
