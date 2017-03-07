// ProgrammeTechnicFundDoc.cpp : implementation of the CProgrammeTechnicFundDoc class
//

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"

#include "ProgrammeTechnicFundDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundDoc

IMPLEMENT_DYNCREATE(CProgrammeTechnicFundDoc, CDocument)

BEGIN_MESSAGE_MAP(CProgrammeTechnicFundDoc, CDocument)
	//{{AFX_MSG_MAP(CProgrammeTechnicFundDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundDoc construction/destruction

CProgrammeTechnicFundDoc::CProgrammeTechnicFundDoc()
{
	// TODO: add one-time construction code here

}

CProgrammeTechnicFundDoc::~CProgrammeTechnicFundDoc()
{
}

BOOL CProgrammeTechnicFundDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundDoc serialization

void CProgrammeTechnicFundDoc::Serialize(CArchive& ar)
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
// CProgrammeTechnicFundDoc diagnostics

#ifdef _DEBUG
void CProgrammeTechnicFundDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProgrammeTechnicFundDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundDoc commands
