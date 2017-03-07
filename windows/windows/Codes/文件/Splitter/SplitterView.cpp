// SplitterView.cpp : implementation of the CSplitterView class
//

#include "stdafx.h"
#include "Splitter.h"

#include "SplitterDoc.h"
#include "SplitterView.h"

#define MAXFILECANBESPLIT 0x36CCCCC

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterView

IMPLEMENT_DYNCREATE(CSplitterView, CFormView)

BEGIN_MESSAGE_MAP(CSplitterView, CFormView)
	//{{AFX_MSG_MAP(CSplitterView)
	ON_BN_CLICKED(IDC_BROWSE1, OnBrowse1)
	ON_BN_CLICKED(IDC_BROWSE2, OnBrowse2)
	ON_BN_CLICKED(IDC_SPLIT, OnSplit)
	ON_BN_CLICKED(IDC_INCREASEBUTTON, OnIncreasebutton)
	ON_BN_CLICKED(IDC_DECREASEBUTTON, OnDecreasebutton)
	ON_BN_CLICKED(IDC_SELECTFOLDERREBUILD, OnSelectfolderrebuild)
	ON_BN_CLICKED(IDC_SELECTFOLDERSPLIT, OnSelectfoldersplit)
	ON_BN_CLICKED(IDC_REBUILD, OnRebuild)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterView construction/destruction

CSplitterView::CSplitterView()
	: CFormView(CSplitterView::IDD)
{
	//{{AFX_DATA_INIT(CSplitterView)
	m_RebuildFile = _T("");
	m_SplitFilePath = _T("");
	m_SelectFolderRebuild = _T("");
	m_SelectFolderSplit = _T("");
	m_SplitNum = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	InitSplitNum();
	//AfxMessageBox("“告诉你一个不好的消息，菜单及工具按钮均不可用。不好意思！:)”",MB_ICONEXCLAMATION|MB_OK);
	//SourcePath=_T("");
}

CSplitterView::~CSplitterView()
{
}

void CSplitterView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplitterView)
	DDX_Control(pDX, IDC_SPLITNUM, m_SplitNumCtrl);
	DDX_Text(pDX, IDC_REBUILDEDIT, m_RebuildFile);
	DDX_Text(pDX, IDC_SPLITEDIT, m_SplitFilePath);
	DDX_Text(pDX, IDC_SELECTFOLDEREDITREBUILD, m_SelectFolderRebuild);
	DDX_Text(pDX, IDC_SELECTFOLDEREDITSPLIT, m_SelectFolderSplit);
	DDX_Text(pDX, IDC_SPLITNUM, m_SplitNum);
	//}}AFX_DATA_MAP
}

BOOL CSplitterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSplitterView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView printing

BOOL CSplitterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSplitterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSplitterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSplitterView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView diagnostics

#ifdef _DEBUG
void CSplitterView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSplitterView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSplitterDoc* CSplitterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitterDoc)));
	return (CSplitterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitterView message handlers

void CSplitterView::OnBrowse1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog Dlg1(TRUE,_T("*"),_T("*.*"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("所有类型文件(*.*)|*.*|"));
	if(IDOK==Dlg1.DoModal())
	{
		m_SplitFilePath.Format("%s",Dlg1.GetPathName());
		m_SplitFileName.Format("%s",Dlg1.GetFileName());
		SetDlgItemText(IDC_SPLITEDIT,m_SplitFilePath);
	    bBrowse1Flag=1;
//----------------------------
		CFile f(m_SplitFilePath,CFile::modeRead);
		FSLength=(LONG)f.GetLength();
		AVLength=FSLength/m_SplitNum;
		LSTLength=FSLength-AVLength*(m_SplitNum-1);
		SetDlgItemInt(IDC_AVFILELENGTH,AVLength,FALSE);
		SetDlgItemInt(IDC_LASTFILELENGTH,LSTLength,FALSE);
		f.Close();
	
	}
}

void CSplitterView::OnBrowse2() 
{
	// TODO: Add your control notification handler code here
	CFileDialog Dlg2(TRUE,_T("XXQ"),_T("*.XXQ"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("XXQ类型文件(*.XXQ)|*.XXQ|"));
	if(IDOK==Dlg2.DoModal())
	{
		m_RebuildFilePath.Format("%s",Dlg2.GetPathName());
		m_RebuildFileName.Format("%s",Dlg2.GetFileName());
		SetDlgItemText(IDC_REBUILDEDIT,m_RebuildFilePath);
		bBrowse2Flag=1;
	}
	
}

void CSplitterView::OnSplit() 
{
	// TODO: Add your control notification handler code here
	
	BOOL bUpdate;
	bUpdate=UpdateData(TRUE);
	if(bUpdate)
	{
		if(!GetDlgItemText(IDC_SPLITEDIT,m_SplitFilePath))
		{
			AfxMessageBox("“您没有输入或选定文件名！”",MB_ICONEXCLAMATION|MB_OK);
		}
		else
		{
			m_SplitNum=GetDlgItemInt(IDC_SPLITNUM,NULL,FALSE);
			if(m_SplitNum<2||m_SplitNum>40)
			{	
				AfxMessageBox("“对不起,分割份数只能在2至20之间！太多了也没什么意义！您说对吗?”",MB_ICONEXCLAMATION|MB_OK);
			}
			else
			{

			int nSaveSplitDir;
			nSaveSplitDir=GetDlgItemText(IDC_SELECTFOLDEREDITSPLIT,m_SelectFolderSplit);
			if(!nSaveSplitDir)
			{
				AfxMessageBox("“您没有指定存放文件夹！”",MB_ICONEXCLAMATION|MB_OK);
			}
			else
			{
			char* pBuffer[0x1000];
			CFile SF(m_SplitFilePath,CFile::modeRead);

			if(!bBrowse1Flag)
			{
				m_SplitFileName=SF.GetFileName();
			}
			
			FSLength=(LONG)SF.GetLength();
			AVLength=FSLength/m_SplitNum;
			LSTLength=FSLength-AVLength*(m_SplitNum-1);
			SetDlgItemInt(IDC_AVFILELENGTH,AVLength,FALSE);
			SetDlgItemInt(IDC_LASTFILELENGTH,LSTLength,FALSE);
			
			UINT i;
			UINT nBytesRead;
			UINT nAV=AVLength/(0x1000);//(4*1024);
			UINT nLST=LSTLength/(0x1000);//(4*1024);

			int nStringLen;
			nStringLen=m_SelectFolderSplit.GetLength();

			switch(m_SplitNum)
			{
			case 20:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str20=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X20");
				CFile f20(str20,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f20.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f20.Write(pBuffer,nBytesRead);
				}
				f20.Close();				
				}
				else
				{
				str20=m_SelectFolderSplit+m_SplitFileName+_T(".X20");
				CFile f20(str20,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f20.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f20.Write(pBuffer,nBytesRead);
				}
				f20.Close();				
				}
				
			case 19:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str19=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X19");
				CFile f19(str19,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f19.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f19.Write(pBuffer,nBytesRead);
				}
				f19.Close();				
				}
				else
				{
				str19=m_SelectFolderSplit+m_SplitFileName+_T(".X19");
				CFile f19(str19,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f19.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f19.Write(pBuffer,nBytesRead);
				}
				f19.Close();				
				}



			case 18:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str18=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X18");
				CFile f18(str18,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f18.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f18.Write(pBuffer,nBytesRead);
				}
				f18.Close();				
				}
				else
				{
				str18=m_SelectFolderSplit+m_SplitFileName+_T(".X18");
				CFile f18(str18,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f18.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f18.Write(pBuffer,nBytesRead);
				}
				f18.Close();				
				}



			case 17:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str17=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X17");
				CFile f17(str17,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f17.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f17.Write(pBuffer,nBytesRead);
				}
				f17.Close();				
				}
				else
				{
				str17=m_SelectFolderSplit+m_SplitFileName+_T(".X17");
				CFile f17(str17,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f17.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f17.Write(pBuffer,nBytesRead);
				}
				f17.Close();				
				}



			case 16:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str16=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X16");
				CFile f16(str16,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f16.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f16.Write(pBuffer,nBytesRead);
				}
				f16.Close();			
				}
				else
				{
				str16=m_SelectFolderSplit+m_SplitFileName+_T(".X16");
				CFile f16(str16,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f16.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f16.Write(pBuffer,nBytesRead);
				}
				f16.Close();			
				}



			case 15:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str19=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X15");
				CFile f15(str15,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f15.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f15.Write(pBuffer,nBytesRead);
				}
				f15.Close();				
				}
				else
				{
				str15=m_SelectFolderSplit+m_SplitFileName+_T(".X15");
				CFile f15(str15,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f15.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f15.Write(pBuffer,nBytesRead);
				}
				f15.Close();				
				}



			case 14:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str14=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X14");
				CFile f14(str14,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f14.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f14.Write(pBuffer,nBytesRead);
				}
				f14.Close();				
				}
				else
				{
				str14=m_SelectFolderSplit+m_SplitFileName+_T(".X14");
				CFile f14(str14,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f14.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f14.Write(pBuffer,nBytesRead);
				}
				f14.Close();				
				}



			case 13:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str13=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X13");
				CFile f13(str13,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f13.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f13.Write(pBuffer,nBytesRead);
				}
				f13.Close();				
				}
				else
				{
				str13=m_SelectFolderSplit+m_SplitFileName+_T(".X13");
				CFile f13(str13,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f13.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f13.Write(pBuffer,nBytesRead);
				}
				f13.Close();				
				}



			case 12:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str12=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X12");
				CFile f12(str12,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f12.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f12.Write(pBuffer,nBytesRead);
				}
				f12.Close();				
				}
				else
				{
				str12=m_SelectFolderSplit+m_SplitFileName+_T(".X12");
				CFile f12(str12,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f12.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f12.Write(pBuffer,nBytesRead);
				}
				f12.Close();				
				}



			case 11:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str11=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X11");
				CFile f11(str11,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f11.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f11.Write(pBuffer,nBytesRead);
				}
				f11.Close();				
				}
				else
				{
				str11=m_SelectFolderSplit+m_SplitFileName+_T(".X11");
				CFile f11(str11,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f11.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f11.Write(pBuffer,nBytesRead);
				}
				f11.Close();				
				}

			case 10:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str10=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X10");
				CFile f10(str10,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f10.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f10.Write(pBuffer,nBytesRead);
				}
				f10.Close();				
				}
				else
				{
				str10=m_SelectFolderSplit+m_SplitFileName+_T(".X10");
				CFile f10(str10,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f10.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f10.Write(pBuffer,nBytesRead);
				}
				f10.Close();				
				}

			case 9:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str9=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X09");
				CFile f9(str9,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f9.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f9.Write(pBuffer,nBytesRead);
				}
				f9.Close();				
				}
				else
				{
				str9=m_SelectFolderSplit+m_SplitFileName+_T(".X09");
				CFile f9(str9,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f9.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f9.Write(pBuffer,nBytesRead);
				}
				f9.Close();				
				}



			case 8:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str8=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X08");
				CFile f8(str8,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f8.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f8.Write(pBuffer,nBytesRead);
				}
				f8.Close();			
				}
				else
				{
				str8=m_SelectFolderSplit+m_SplitFileName+_T(".X08");
				CFile f8(str8,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f8.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f8.Write(pBuffer,nBytesRead);
				}
				f8.Close();				
				}



			case 7:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str7=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X07");
				CFile f7(str7,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f7.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f7.Write(pBuffer,nBytesRead);
				}
				f7.Close();				
				}
				else
				{
				str7=m_SelectFolderSplit+m_SplitFileName+_T(".X07");
				CFile f7(str7,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f7.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f7.Write(pBuffer,nBytesRead);
				}
				f7.Close();				
				}



			case 6:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str6=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X06");
				CFile f6(str6,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f6.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f6.Write(pBuffer,nBytesRead);
				}
				f6.Close();				
				}
				else
				{
				str6=m_SelectFolderSplit+m_SplitFileName+_T(".X06");
				CFile f6(str6,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f6.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f6.Write(pBuffer,nBytesRead);
				}
				f6.Close();				
				}



			case 5:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str5=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X05");
				CFile f5(str5,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f5.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f5.Write(pBuffer,nBytesRead);
				}
				f5.Close();				
				}
				else
				{
				str5=m_SelectFolderSplit+m_SplitFileName+_T(".X05");
				CFile f5(str5,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f5.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f5.Write(pBuffer,nBytesRead);
				}
				f5.Close();			
				}



			case 4:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str4=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X04");
				CFile f4(str4,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f4.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f4.Write(pBuffer,nBytesRead);
				}
				f4.Close();				
				}
				else
				{
				str4=m_SelectFolderSplit+m_SplitFileName+_T(".X04");
				CFile f4(str4,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f4.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f4.Write(pBuffer,nBytesRead);
				}
				f4.Close();				
				}

			case 3:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str3=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X03");
				CFile f3(str3,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f3.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f3.Write(pBuffer,nBytesRead);
				}
				f3.Close();				
				}
				else
				{
				str3=m_SelectFolderSplit+m_SplitFileName+_T(".X03");
				CFile f3(str3,CFile::modeCreate|CFile::modeReadWrite);
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f3.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f3.Write(pBuffer,nBytesRead);
				}
				f3.Close();				
				}

			case 2:
				if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
				{
				str1=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X01");
				str2=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".X02");
				CFile f1(str1,CFile::modeCreate|CFile::modeReadWrite);
				CFile f2(str2,CFile::modeCreate|CFile::modeReadWrite);
				
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f2.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f2.Write(pBuffer,nBytesRead);
				}
				f2.Close();

				for(i=0;i<nLST;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f1.Write(pBuffer,nBytesRead);
				}
				if(nLST*(0x1000)<LSTLength)
				{
					nBytesRead=SF.Read(pBuffer,(LSTLength-nLST*(0x1000)));
					f1.Write(pBuffer,nBytesRead);
				}
				f1.Close();
				break;				
				}
				else
				{
				str1=m_SelectFolderSplit+m_SplitFileName+_T(".X01");
				str2=m_SelectFolderSplit+m_SplitFileName+_T(".X02");
				CFile f1(str1,CFile::modeCreate|CFile::modeReadWrite);
				CFile f2(str2,CFile::modeCreate|CFile::modeReadWrite);
				
				for(i=0;i<nAV;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f2.Write(pBuffer,nBytesRead);
				}
				if(nAV*(0x1000)<AVLength)
				{
					nBytesRead=SF.Read(pBuffer,(AVLength-nAV*(0x1000)));
					f2.Write(pBuffer,nBytesRead);
				}
				f2.Close();

				for(i=0;i<nLST;i++)
				{
					nBytesRead=SF.Read(pBuffer,0x1000);
					f1.Write(pBuffer,nBytesRead);
				}
				if(nLST*(0x1000)<LSTLength)
				{
					nBytesRead=SF.Read(pBuffer,(LSTLength-nLST*(0x1000)));
					f1.Write(pBuffer,nBytesRead);
				}
				f1.Close();
				break;				
				}

    		default:
				AfxMessageBox("“对不起,分割文件没有成功！可能您的操作有误。”",MB_ICONEXCLAMATION|MB_OK);
				break;
			}
			SF.Close();


			///////Clear files size.
			//SetDlgItemInt(IDC_AVFILELENGTH,0,FALSE);
			//SetDlgItemInt(IDC_LASTFILELENGTH,0,FALSE);


			//Create *.XXQ file.
			if(m_SelectFolderSplit.GetAt(nStringLen-1)!='\\')
			{
				CString str_xxq=m_SelectFolderSplit+_T("\\")+m_SplitFileName+_T(".XXQ");
				CFile f_xxq(str_xxq,CFile::modeCreate|CFile::modeReadWrite);
				UINT* pBff;
				pBff=&m_SplitNum;
				f_xxq.Write(pBff,sizeof(UINT));
				f_xxq.Close();
			}
			else
			{
				CString str_xxq=m_SelectFolderSplit+m_SplitFileName+_T(".XXQ");
				CFile f_xxq(str_xxq,CFile::modeCreate|CFile::modeReadWrite);
				UINT* pBff;

				pBff=&m_SplitNum;
				f_xxq.Write(pBff,sizeof(UINT));
				f_xxq.Close();	
			}
			AfxMessageBox("“文件分割成功！”",MB_ICONEXCLAMATION|MB_OK);
			CString m_tmpSplitFilePath=_T("");
			SetDlgItemText(IDC_SPLITEDIT,m_tmpSplitFilePath);			
			
			///////Clear files size.
			SetDlgItemInt(IDC_AVFILELENGTH,0,FALSE);
			SetDlgItemInt(IDC_LASTFILELENGTH,0,FALSE);
			
			//resume original setting.
			SetDlgItemInt(IDC_SPLITNUM,2,FALSE);
			SetDlgItemText(IDC_SELECTFOLDEREDITSPLIT,NULL);

			}
			}
		}
	}
}

void CSplitterView::OnIncreasebutton() 
{
	// TODO: Add your control notification handler code here
	BOOL bUpData;
	bUpData=UpdateData(TRUE);
	if(bUpData)
	{
		if(!GetDlgItemText(IDC_SPLITEDIT,m_SplitFilePath))
			AfxMessageBox("“您没有输入或选定文件名！”",MB_ICONEXCLAMATION|MB_OK);
		else
		{
			m_SplitNum=GetDlgItemInt(IDC_SPLITNUM,NULL,FALSE);
			if(m_SplitNum>=20)
			{
				AfxMessageBox("“对不起,分割份数只能在2至20之间！作者认为太多了也没多大意思！”",MB_ICONINFORMATION|MB_OK);
			}
			else
			{
				m_SplitNum++;
				SetDlgItemInt(IDC_SPLITNUM,m_SplitNum,FALSE);
				CFile fIn(m_SplitFilePath,CFile::modeRead);
				FSLength=(LONG)fIn.GetLength();
				AVLength=FSLength/m_SplitNum;
				LSTLength=FSLength-AVLength*(m_SplitNum-1);
				SetDlgItemInt(IDC_AVFILELENGTH,AVLength,FALSE);
				SetDlgItemInt(IDC_LASTFILELENGTH,LSTLength,FALSE);
				fIn.Close();
			}
		}
	}
}

void CSplitterView::OnDecreasebutton() 
{
	// TODO: Add your control notification handler code here
	BOOL bUpData;
	bUpData=UpdateData(TRUE);
	if(bUpData)
	{
		if(!GetDlgItemText(IDC_SPLITEDIT,m_SplitFilePath))
			AfxMessageBox("“您没有输入或选定文件名！”",MB_ICONEXCLAMATION|MB_OK);
		else
		{
			m_SplitNum=GetDlgItemInt(IDC_SPLITNUM,NULL,FALSE);
			if(m_SplitNum<=2||m_SplitNum>20)
			{
				AfxMessageBox("“对不起,分割份数只能在2至20之间！太多了也没多大意思！”",MB_ICONINFORMATION|MB_OK);
			}
			else
			{
				m_SplitNum--;
				SetDlgItemInt(IDC_SPLITNUM,m_SplitNum,FALSE);
				CFile fDe(m_SplitFilePath,CFile::modeRead);
				FSLength=(LONG)fDe.GetLength();
				AVLength=FSLength/m_SplitNum;
				LSTLength=FSLength-AVLength*(m_SplitNum-1);
				SetDlgItemInt(IDC_AVFILELENGTH,AVLength,FALSE);
				SetDlgItemInt(IDC_LASTFILELENGTH,LSTLength,FALSE);
				fDe.Close();
			}
		}
	}
}

void CSplitterView::OnSelectfolderrebuild() 
{
	// TODO: Add your control notification handler code here
	if(m_DirDialogRebuild.DoBrowse())
	{
		//  from DirDialog.h,DirDialog.cpp: 2001-03-05 by xxq.
		m_SelectFolderRebuild=m_DirDialogRebuild.m_strPath;
		SetDlgItemText(IDC_SELECTFOLDEREDITREBUILD,m_SelectFolderRebuild);
	}	
}

void CSplitterView::OnSelectfoldersplit() 
{
	// TODO: Add your control notification handler code here
	if(m_DirDialogSplit.DoBrowse())
	{
		//  from DirDialog.h,DirDialog.cpp: 2001-03-05 by xxq.
		m_SelectFolderSplit=m_DirDialogSplit.m_strPath;
		SetDlgItemText(IDC_SELECTFOLDEREDITSPLIT,m_SelectFolderSplit);
	}	
}


void CSplitterView::OnRebuild() 
{
	// TODO: Add your control notification handler code here
	BOOL bCheck;
	bCheck=UpdateData(TRUE);
	if(!bCheck)
	{
		AfxMessageBox("“您的操作可能有误！”",MB_ICONEXCLAMATION|MB_OK);
	}
	else
	{
		int nCheck;
		nCheck=GetDlgItemText(IDC_REBUILDEDIT,m_RebuildFile);
		if(!nCheck)
		{
			AfxMessageBox("“您没有指定 XXQ 类型文件！”",MB_ICONEXCLAMATION|MB_OK);
		}
		else
		{
			int nCheckSaveDir;
			nCheckSaveDir=GetDlgItemText(IDC_SELECTFOLDEREDITREBUILD,m_SelectFolderRebuild);
			if(!nCheckSaveDir)
			{
				AfxMessageBox("“您没有指定存放文件夹！”",MB_ICONEXCLAMATION|MB_OK);	
			}
			else//starting rebuild!
			{
				CString SourceFileName=_T("");
				CFile tempFile(m_RebuildFile,CFile::modeRead);
				SourceFileName=tempFile.GetFileName();
				UINT nSrcFileNameLen;
				nSrcFileNameLen=SourceFileName.GetLength();
				SourceFileName=SourceFileName.Mid(0,nSrcFileNameLen-4);
				tempFile.Close();

				CString FinalFile=_T("");
				int nSaveDirLen;
				nSaveDirLen=m_SelectFolderRebuild.GetLength();
				if(m_SelectFolderRebuild[nSaveDirLen-1]!='\\')
				//if(m_SelectFolderRebuild.GetAt(nSaveDirLen-1)!='\\')
				{
					FinalFile=m_SelectFolderRebuild+_T("\\")+SourceFileName;
				}
				else
				{
					FinalFile=m_SelectFolderRebuild+SourceFileName;
				}

				CString SourcePath=_T("");
				UINT nSrcPath;
				nSrcPath=m_RebuildFile.GetLength();
				SourcePath=m_RebuildFile.Mid(0,nSrcPath-4);
				UINT nNum;
				UINT* pBff;
				pBff=&nNum;
				UINT nBytesRead;

				UINT i;

				CFile RbF(m_RebuildFile,CFile::modeRead);
				/////RbF is XXQ File.
				nBytesRead=RbF.Read(pBff,sizeof(UINT));
				nNum=*pBff;
				RbF.Close();

				char* pB[0x1000];
				CFile Finalf(FinalFile,CFile::modeCreate|CFile::modeWrite);
				switch(nNum)
				{
					case 20:
						{
							s20=SourcePath+_T(".X20");
							CFile f20(s20,CFile::modeRead);
							UINT nf20Len;						
							nf20Len=f20.GetLength();
							UINT nf20Block;//=nf20Len/(0x1000);
							nf20Block=nf20Len/(0x1000);
							for(i=0;i<nf20Block;i++)
							{
								nBytesRead=f20.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf20Block*(0x1000)<nf20Len)
							{
								nBytesRead=f20.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f20.Close();
						}

					case 19:
						{
							s19=SourcePath+_T(".X19");
							CFile f19(s19,CFile::modeRead);
							UINT nf19Len;
							nf19Len=f19.GetLength();
							UINT nf19Block;
							nf19Block=nf19Len/(0x1000);
							for(i=0;i<nf19Block;i++)
							{
								nBytesRead=f19.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf19Block*(0x1000)<nf19Len)
							{
								nBytesRead=f19.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f19.Close();
						}
					case 18:
						{
							s18=SourcePath+_T(".X18");
							CFile f18(s18,CFile::modeRead);
							UINT nf18Len;
							nf18Len=f18.GetLength();
							UINT nf18Block;
							nf18Block=nf18Len/(0x1000);
							for(i=0;i<nf18Block;i++)
							{
								nBytesRead=f18.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf18Block*(0x1000)<nf18Len)
							{
								nBytesRead=f18.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f18.Close();
						}
					case 17:
						{
							s17=SourcePath+_T(".X17");
							CFile f17(s17,CFile::modeRead);
							UINT nf17Len;
							nf17Len=f17.GetLength();
							UINT nf17Block;
							nf17Block=nf17Len/(0x1000);
							for(i=0;i<nf17Block;i++)
							{
								nBytesRead=f17.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf17Block*(0x1000)<nf17Len)
							{
								nBytesRead=f17.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f17.Close();
						}

					case 16:
						{
							s16=SourcePath+_T(".X16");
							CFile f16(s16,CFile::modeRead);
							UINT nf16Len;
							nf16Len=f16.GetLength();
							UINT nf16Block;
							nf16Block=nf16Len/(0x1000);
							for(i=0;i<nf16Block;i++)
							{
								nBytesRead=f16.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf16Block*(0x1000)<nf16Len)
							{
								nBytesRead=f16.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f16.Close();
						}
					case 15:
						{
							s15=SourcePath+_T(".X15");
							CFile f15(s15,CFile::modeRead);
							UINT nf15Len;
							nf15Len=f15.GetLength();
							UINT nf15Block;
							nf15Block=nf15Len/(0x1000);
							for(i=0;i<nf15Block;i++)
							{
								nBytesRead=f15.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf15Block*(0x1000)<nf15Len)
							{
								nBytesRead=f15.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
						}
					case 14:
						{
							s14=SourcePath+_T(".X14");
							CFile f14(s14,CFile::modeRead);
							UINT nf14Len;
							nf14Len=f14.GetLength();
							UINT nf14Block;
							nf14Block=nf14Len/(0x1000);
							for(i=0;i<nf14Block;i++)
							{
								nBytesRead=f14.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf14Block*(0x1000)<nf14Len)
							{
								nBytesRead=f14.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f14.Close();
						}
					case 13:
						{
							s13=SourcePath+_T(".X13");
							CFile f13(s13,CFile::modeRead);
							UINT nf13Len;
							nf13Len=f13.GetLength();
							UINT nf13Block;
							nf13Block=nf13Len/(0x1000);
							for(i=0;i<nf13Block;i++)
							{
								nBytesRead=f13.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf13Block*(0x1000)<nf13Len)
							{
								nBytesRead=f13.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f13.Close();
						}
					case 12:
						{
							s12=SourcePath+_T(".X12");
							CFile f12(s12,CFile::modeRead);
							UINT nf12Len;
							nf12Len=f12.GetLength();
							UINT nf12Block;
							nf12Block=nf12Len/(0x1000);
							for(i=0;i<nf12Block;i++)
							{
								nBytesRead=f12.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf12Block*(0x1000)<nf12Len)
							{
								nBytesRead=f12.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f12.Close();
						}
					case 11:
						{
							s11=SourcePath+_T(".X11");
							CFile f11(s11,CFile::modeRead);
							UINT nf11Len;
							nf11Len=f11.GetLength();
							UINT nf11Block;
							nf11Block=nf11Len/(0x1000);
							for(i=0;i<nf11Block;i++)
							{
								nBytesRead=f11.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf11Block*(0x1000)<nf11Len)
							{
								nBytesRead=f11.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f11.Close();
						}
					case 10:
						{
							s10=SourcePath+_T(".X10");
							CFile f10(s10,CFile::modeRead);
							UINT nf10Len;
							nf10Len=f10.GetLength();
							UINT nf10Block;
							nf10Block=nf10Len/(0x1000);
							for(i=0;i<nf10Block;i++)
							{
								nBytesRead=f10.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf10Block*(0x1000)<nf10Len)
							{
								nBytesRead=f10.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f10.Close();
						}
					case 9:
						{
							s9=SourcePath+_T(".X09");
							CFile f9(s9,CFile::modeRead);
							UINT nf9Len;
							nf9Len=f9.GetLength();
							UINT nf9Block;
							nf9Block=nf9Len/(0x1000);
							for(i=0;i<nf9Block;i++)
							{
								nBytesRead=f9.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf9Block*(0x1000)<nf9Len)
							{
								nBytesRead=f9.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f9.Close();
						}
					case 8:
						{
							s8=SourcePath+_T(".X08");
							CFile f8(s8,CFile::modeRead);
							UINT nf8Len;
							nf8Len=f8.GetLength();
							UINT nf8Block;
							nf8Block=nf8Len/(0x1000);
							for(i=0;i<nf8Block;i++)
							{
								nBytesRead=f8.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf8Block*(0x1000)<nf8Len)
							{
								nBytesRead=f8.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f8.Close();
						}
					case 7:
						{
							s7=SourcePath+_T(".X07");
							CFile f7(s7,CFile::modeRead);
							UINT nf7Len;
							nf7Len=f7.GetLength();
							UINT nf7Block;
							nf7Block=nf7Len/(0x1000);
							for(i=0;i<nf7Block;i++)
							{
								nBytesRead=f7.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf7Block*(0x1000)<nf7Len)
							{
								nBytesRead=f7.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f7.Close();
						}
					case 6:
						{
							s6=SourcePath+_T(".X06");
							CFile f6(s6,CFile::modeRead);
							UINT nf6Len;
							nf6Len=f6.GetLength();
							UINT nf6Block;
							nf6Block=nf6Len/(0x1000);
							for(i=0;i<nf6Block;i++)
							{
								nBytesRead=f6.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf6Block*(0x1000)<nf6Len)
							{
								nBytesRead=f6.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f6.Close();
						}
					case 5:
						{
							s5=SourcePath+_T(".X05");
							CFile f5(s5,CFile::modeRead);
							UINT nf5Len;
							nf5Len=f5.GetLength();
							UINT nf5Block;
							nf5Block=nf5Len/(0x1000);
							for(i=0;i<nf5Block;i++)
							{
								nBytesRead=f5.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf5Block*(0x1000)<nf5Len)
							{
								nBytesRead=f5.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f5.Close();
						}
					case 4:
						{
							s4=SourcePath+_T(".X04");
							CFile f4(s4,CFile::modeRead);
							UINT nf4Len;
							nf4Len=f4.GetLength();
							UINT nf4Block;
							nf4Block=nf4Len/(0x1000);
							for(i=0;i<nf4Block;i++)
							{
								nBytesRead=f4.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf4Block*(0x1000)<nf4Len)
							{
								nBytesRead=f4.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f4.Close();
						}
					case 3:
						{
							s3=SourcePath+_T(".X03");
							CFile f3(s3,CFile::modeRead);
							UINT nf3Len;
							nf3Len=f3.GetLength();
							UINT nf3Block;
							nf3Block=nf3Len/(0x1000);
							for(i=0;i<nf3Block;i++)
							{
								nBytesRead=f3.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf3Block*(0x1000)<nf3Len)
							{
								nBytesRead=f3.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f3.Close();
						}

					case 2:
						{
							s2=SourcePath+_T(".X02");
							CFile f2(s2,CFile::modeRead);
							UINT nf2Len;
							nf2Len=f2.GetLength();
							UINT nf2Block;
							nf2Block=nf2Len/(0x1000);
							for(i=0;i<nf2Block;i++)
							{
								nBytesRead=f2.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf2Block*(0x1000)<nf2Len)
							{
								nBytesRead=f2.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f2.Close();

							s1=SourcePath+_T(".X01");
							CFile f1(s1,CFile::modeRead);
							UINT nf1Len;
							nf1Len=f1.GetLength();
							UINT nf1Block;
							nf1Block=nf1Len/(0x1000);
							for(i=0;i<nf1Block;i++)
							{
								nBytesRead=f1.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							if(nf1Block*(0x1000)<nf1Len)
							{
								nBytesRead=f1.Read(pB,0x1000);
								Finalf.Write(pB,nBytesRead);
							}
							f1.Close();
							break;
						}
					default:
						AfxMessageBox("“对不起,合并文件没有成功！可能您的操作有误。”",MB_ICONEXCLAMATION|MB_OK);
						break;
				}
				Finalf.Close();
				AfxMessageBox("“文件合并成功！”",MB_ICONEXCLAMATION|MB_OK);
				m_RebuildFile=_T("");
				m_SelectFolderRebuild=_T("");
				SetDlgItemText(IDC_REBUILDEDIT,m_RebuildFile);
				SetDlgItemText(IDC_SELECTFOLDEREDITREBUILD,m_SelectFolderRebuild);
			}
		}
	}	
}
