// ProgrammeTechnicAccumulateDoc.cpp : implementation of the CProgrammeTechnicAccumulateDoc class
//

#include "stdafx.h"
#include "ProgrammeTechnicAccumulate.h"

#include "ProgrammeTechnicAccumulateDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateDoc

IMPLEMENT_DYNCREATE(CProgrammeTechnicAccumulateDoc, CDocument)

BEGIN_MESSAGE_MAP(CProgrammeTechnicAccumulateDoc, CDocument)
	//{{AFX_MSG_MAP(CProgrammeTechnicAccumulateDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateDoc construction/destruction

CProgrammeTechnicAccumulateDoc::CProgrammeTechnicAccumulateDoc()
{
	// TODO: add one-time construction code here

}

CProgrammeTechnicAccumulateDoc::~CProgrammeTechnicAccumulateDoc()
{
}

BOOL CProgrammeTechnicAccumulateDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateDoc serialization

void CProgrammeTechnicAccumulateDoc::Serialize(CArchive& ar)
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
// CProgrammeTechnicAccumulateDoc diagnostics

#ifdef _DEBUG
void CProgrammeTechnicAccumulateDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProgrammeTechnicAccumulateDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateDoc commands
