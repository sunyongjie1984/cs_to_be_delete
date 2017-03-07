// xiongFtpDoc.cpp : implementation of the CFtpClientDoc class
//

#include "stdafx.h"
#include "FtpClient.h"

#include "FtpClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFtpClientDoc

IMPLEMENT_DYNCREATE(CFtpClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CFtpClientDoc, CDocument)
	//{{AFX_MSG_MAP(CFtpClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpClientDoc construction/destruction

CFtpClientDoc::CFtpClientDoc()
{
	// TODO: add one-time construction code here

}

CFtpClientDoc::~CFtpClientDoc()
{
}

BOOL CFtpClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFtpClientDoc serialization

void CFtpClientDoc::Serialize(CArchive& ar)
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
// CFtpClientDoc diagnostics

#ifdef _DEBUG
void CFtpClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFtpClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFtpClientDoc commands
