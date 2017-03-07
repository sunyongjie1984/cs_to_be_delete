// SafetyCodeDoc.cpp : implementation of the CSafetyCodeDoc class
//

#include "stdafx.h"
#include "SafetyCode.h"

#include "SafetyCodeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeDoc

IMPLEMENT_DYNCREATE(CSafetyCodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CSafetyCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CSafetyCodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeDoc construction/destruction

CSafetyCodeDoc::CSafetyCodeDoc()
{
	// TODO: add one-time construction code here

}

CSafetyCodeDoc::~CSafetyCodeDoc()
{
}

BOOL CSafetyCodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeDoc serialization

void CSafetyCodeDoc::Serialize(CArchive& ar)
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
// CSafetyCodeDoc diagnostics

#ifdef _DEBUG
void CSafetyCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSafetyCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeDoc commands
