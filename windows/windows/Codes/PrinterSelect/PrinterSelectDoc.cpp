// PrinterSelectDoc.cpp : implementation of the CPrinterSelectDoc class
//

#include "stdafx.h"
#include "PrinterSelect.h"

#include "PrinterSelectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDoc

IMPLEMENT_DYNCREATE(CPrinterSelectDoc, CDocument)

BEGIN_MESSAGE_MAP(CPrinterSelectDoc, CDocument)
	//{{AFX_MSG_MAP(CPrinterSelectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDoc construction/destruction

CPrinterSelectDoc::CPrinterSelectDoc()
{
	// TODO: add one-time construction code here

}

CPrinterSelectDoc::~CPrinterSelectDoc()
{
}

BOOL CPrinterSelectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDoc serialization

void CPrinterSelectDoc::Serialize(CArchive& ar)
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
// CPrinterSelectDoc diagnostics

#ifdef _DEBUG
void CPrinterSelectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrinterSelectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDoc commands
