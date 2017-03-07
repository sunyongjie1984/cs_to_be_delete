           // DialogEntropy.cpp : implementation file
//

#include "stdafx.h"
#include "NewTab.h"
#include "DialogEntropy.h"

extern En_Decode Coder;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogEntropy dialog


CDialogEntropy::CDialogEntropy(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CDialogEntropy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogEntropy)
	m_bEnDeCode = 0;
	//}}AFX_DATA_INIT
}


void CDialogEntropy::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogEntropy)
	DDX_Radio(pDX, IDC_RADIO_ENCODE, m_bEnDeCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogEntropy, CTabPageSSL)
	//{{AFX_MSG_MAP(CDialogEntropy)
	ON_BN_CLICKED(IDC_BUTTON_Open, OnBUTTONOpen)
	ON_BN_CLICKED(IDC_BUTTON_Decode, OnBUTTONDecode)
	ON_BN_CLICKED(IDC_RADIO_DECODE, OnRadioDecode)
	ON_BN_CLICKED(IDC_RADIO_ENCODE, OnRadioEncode)
	ON_BN_CLICKED(IDC_BUTTON_DESTFILE, OnButtonDestfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEntropy message handlers

void CDialogEntropy::OnBUTTONOpen()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY,"All Files(*.*)|*.*|",this);
	fileDialog.m_ofn.Flags|=OFN_EXPLORER;
	if(fileDialog.DoModal() != IDOK)
		return;
	CString strFilename=fileDialog.GetPathName();
	CEdit *inEdit;
	inEdit = (CEdit *)GetDlgItem(IDC_EDIT_INFILE);
	inEdit->SetWindowText(strFilename);
	lstrcpy(InFileName, strFilename);
	strFilename=fileDialog.GetFileExt();
	lstrcpy(ExtName, strFilename);
	Coder.SetInputFileName(InFileName, ExtName);
}

void CDialogEntropy::OnBUTTONDecode() 
{
	// TODO: Add your control notification handler code here
	if (m_bEnDeCode)
		Coder.Decode();
	else
		Coder.Encode();
	SetFileInfo();
}

BOOL CDialogEntropy::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	
	// TODO: Add extra initialization here
//	CSpinButtonCtrl* pBoxOne;
//	pBoxOne = (CSpinButtonCtrl*) GetDlgItem(IDC_RADIO_ENCODE);
//	pBoxOne

	//GetDlgItem(IDC_RADIO_ENCODE) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogEntropy::OnRadioDecode() 
{
	// TODO: Add your control notification handler code here
	m_bEnDeCode = 1;
}

void CDialogEntropy::OnRadioEncode() 
{
	// TODO: Add your control notification handler code here
	m_bEnDeCode = 0;
}

void CDialogEntropy::OnButtonDestfile() 
{
	// TODO: Add your control notification handler code here
	if (m_bEnDeCode)
	{
		Coder.GetExtName(ExtName);
		CString temp;
		CString strFilename("Source File(*.");
		temp.Format("%s", ExtName);
		strFilename += temp;
		temp.Format("%s", ")|*.");
		strFilename += temp;
		temp.Format("%s", ExtName);
		strFilename += temp;
		temp.Format("%s", "|");
		strFilename += temp;
		char szFilter[30];
		lstrcpy(szFilter, strFilename);
		CFileDialog fileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFilter,this);
		fileDialog.m_ofn.Flags |= OFN_EXPLORER;
		if(fileDialog.DoModal() != IDOK)
			return;
		strFilename = fileDialog.GetPathName();
		temp.Format(".%s", ExtName);
		strFilename += temp;
		CEdit *inEdit;
		inEdit = (CEdit *)GetDlgItem(IDC_EDIT_OUTFILE);
		inEdit->SetWindowText(strFilename);
		lstrcpy(OutFileName, strFilename);
		Coder.SetOutputFileName(OutFileName);
	}
	else
	{
		CFileDialog fileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY,"All Files(*.*)|*.*|",this);
		fileDialog.m_ofn.Flags|=OFN_EXPLORER;
		if(fileDialog.DoModal() != IDOK)
			return;
		CString strFilename = fileDialog.GetPathName();
		CEdit *inEdit;
		inEdit = (CEdit *)GetDlgItem(IDC_EDIT_OUTFILE);
		inEdit->SetWindowText(strFilename);
		TCHAR sz[256];
		lstrcpy(sz, strFilename);
		Coder.SetOutputFileName(sz);
	}
}

void CDialogEntropy::SetFileInfo()
{
	CString str;
	CEdit *inEdit;
	unsigned int i = Coder.GetActualDataLength();
	unsigned int j = Coder.GetUncodedFileLength();
	double t = static_cast<double>(i);
	t /= j;

	str.Format("%d", j);
	inEdit = (CEdit *)GetDlgItem(IDC_STATIC_SOURCELENGTH);
	inEdit->SetWindowText(str);

	str.Format("%f", Coder.GetUncodedFileCodeLength() );
	inEdit = (CEdit *)GetDlgItem(IDC_STATIC_ENTROPY);
	inEdit->SetWindowText(str);

	str.Format("%f", Coder.GetSourceFileEntropy());
	inEdit = (CEdit *)GetDlgItem(IDC_STATIC_CODELENGTH);
	inEdit->SetWindowText(str);

	str.Format("%d", Coder.GetActiveSymbols());
	inEdit = (CEdit *)GetDlgItem(IDC_STATIC_HEAD_LENGTH);
	inEdit->SetWindowText(str);

	str.Format("%d", i);
	inEdit = (CEdit *)GetDlgItem(IDC_STATIC_ACTUAL_LENGTH);
	inEdit->SetWindowText(str);

	str.Format("%f", t);
	inEdit = (CEdit *)GetDlgItem(IDC_STATIC_RATE);
	inEdit->SetWindowText(str);

//	delete inEdit;
}
