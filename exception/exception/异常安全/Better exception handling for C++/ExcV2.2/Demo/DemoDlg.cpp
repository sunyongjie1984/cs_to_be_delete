// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"

#include "../Excpt/Excpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning (disable: 4722)	// d'tor throws


// CDemoDlg dialog




CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FRAME_STD, &CDemoDlg::OnBnClickedFrameStd)
	ON_BN_CLICKED(IDC_FRAME_CUST, &CDemoDlg::OnBnClickedFrameCust)
	ON_BN_CLICKED(IDC_THROW_STD, &CDemoDlg::OnBnClickedThrowStd)
	ON_BN_CLICKED(IDC_THROW_CUST, &CDemoDlg::OnBnClickedThrowCust)
	ON_BN_CLICKED(IDC_TST_SPEED, &CDemoDlg::OnBnClickedTstSpeed)
	ON_BN_CLICKED(IDC_TST_DTOR, &CDemoDlg::OnBnClickedTstDtor)
	ON_BN_CLICKED(IDC_TST_INLINE, &CDemoDlg::OnBnClickedTstInline)
	ON_BN_CLICKED(IDC_TST_NONCPP, &CDemoDlg::OnBnClickedTstNoncpp)
	ON_BN_CLICKED(IDC_TST_STOPEXC, &CDemoDlg::OnBnClickedTstStopexc)
END_MESSAGE_MAP()


// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	((CButton*) GetDlgItem(IDC_FRAME_STD))->SetCheck(BST_CHECKED);
	((CButton*) GetDlgItem(IDC_THROW_STD))->SetCheck(BST_CHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDemoDlg::OnBnClickedFrameStd()
{
	Exc::SetFrameHandler(false);
}

void CDemoDlg::OnBnClickedFrameCust()
{
	Exc::SetFrameHandler(true);
}

void CDemoDlg::OnBnClickedThrowStd()
{
	Exc::SetThrowFunction(false);
}

void CDemoDlg::OnBnClickedThrowCust()
{
	Exc::SetThrowFunction(true);
}

struct ArticulatingObj
{
	CString& m_sLog;
	PCTSTR m_szName;

	BYTE m_pFatBuf[10];

	static void Test(bool b)
	{
		if (!b)
			__debugbreak();
	}

	ArticulatingObj(CString& sLog, PCTSTR szName)
		:m_sLog(sLog)
		,m_szName(szName)
	{
		m_sLog += m_szName;
		m_sLog += _T(": C'tor\r\n");

		for (int i = 0; i < _countof(m_pFatBuf); i++)
			m_pFatBuf[i] = i ^ int(m_szName);
	}
	~ArticulatingObj()
	{
		for (int i = 0; i < _countof(m_pFatBuf); i++)
			Test(m_pFatBuf[i] == BYTE(i ^ int(m_szName)));

		m_sLog += m_szName;
		m_sLog += _T(": D'tor\r\n");
	}
};

void CDemoDlg::OnBnClickedTstDtor()
{
	CString sLog;

	try {

		struct BadObj :public ArticulatingObj {
			BadObj(CString& sLog, PCTSTR szName)
				:ArticulatingObj(sLog, szName)
			{
				m_sLog += m_szName;
				m_sLog += _T(": C'tor (Derived class)\r\n");
			}
			~BadObj()
			{
				m_sLog += m_szName;
				m_sLog += _T(": D'tor (Derived class) - throwing\r\n");
				throw CString(m_szName);
			}
		};

		BadObj a(sLog, _T("A"));
		BadObj b(sLog, _T("B"));
		BadObj c(sLog, _T("C"));
		BadObj d(sLog, _T("D"));

		sLog += _T("Throwing E\r\n");
		throw CString(_T("E"));

	} catch (const CString s)
	{
		CString sTxt;
		sTxt.Format(_T("Caught %s\r\n"), s);
		sLog += sTxt;
	}

	sLog += _T("All finished");

	AfxMessageBox(sLog, MB_ICONINFORMATION);
}

void CDemoDlg::OnBnClickedTstInline()
{
	CString sLog;

	try {

		struct InlineHandler :public Exc::Monitor {
			CString& m_sLog;
			InlineHandler(CString& sLog) :m_sLog(sLog) {}

			virtual bool Handle(EXCEPTION_RECORD* pExc, CONTEXT* pCpuCtx) {
				m_sLog += _T("I see exception\r\n");
				return false;
			}
		} inlHandler(sLog);


		ArticulatingObj a(sLog, _T("A"));
		ArticulatingObj b(sLog, _T("B"));
		ArticulatingObj c(sLog, _T("C"));
		ArticulatingObj d(sLog, _T("D"));

		sLog += _T("Throwing\r\n");
		throw 5;

	} catch (int)
	{
		sLog += _T("Caught\r\n");
	}

	sLog += _T("All finished");

	AfxMessageBox(sLog, MB_ICONINFORMATION);
}

void CDemoDlg::OnBnClickedTstNoncpp()
{
	CString sLog;

	try {

		try {

			struct InlineHandler :public Exc::Monitor {
				CString& m_sLog;
				InlineHandler(CString& sLog) :m_sLog(sLog) {}

				virtual bool Handle(EXCEPTION_RECORD* pExc, CONTEXT* pCpuCtx) {
					CString sTxt;
					sTxt.Format(_T("I see SEH exception. Code=0x%08X\r\n"), pExc->ExceptionCode);
					m_sLog += sTxt;
					return false;
				}
			} inlHandler(sLog);

			ArticulatingObj a(sLog, _T("A"));
			ArticulatingObj b(sLog, _T("B"));
			ArticulatingObj c(sLog, _T("C"));
			ArticulatingObj d(sLog, _T("D"));

			sLog += _T("Accessing invalid memory\r\n");
			*((PBYTE) NULL) = 0;

		} catch (...)
		{
			sLog += _T("Caught\r\n");
		}

	} catch (...)
	{
	}

	sLog += _T("All finished");

	AfxMessageBox(sLog, MB_ICONINFORMATION);
}

BYTE  _safe_se_handler_count = 0;

class CSpeedDlg : public CDialog
{
	// Construction
	volatile bool m_bRun;

	HANDLE m_hThread;

	static const DWORD s_dwTestDuration = 3000; // 3 secs


	static DWORD WINAPI PerfTst(PVOID);

public:

	volatile size_t m_nCycles;
	DWORD m_dwTicks;

	CSpeedDlg(CWnd* pParent = NULL)
		:CDialog(IDD, pParent)
		,m_hThread(NULL)
	{}

	// Dialog Data
	enum { IDD = IDD_SPEED_DIALOG };

protected:
	//virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR);

	DECLARE_MESSAGE_MAP()
public:
};

BEGIN_MESSAGE_MAP(CSpeedDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CSpeedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bRun = true;
	DWORD dwThread;
	m_hThread = CreateThread(NULL, 0, PerfTst, this, 0, &dwThread);
	if (!m_hThread)
		EndDialog(IDCANCEL);
	else
	{
		m_dwTicks = GetTickCount();
		VERIFY(SetTimer(1, 200, NULL));

		CProgressCtrl* pProgress = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS);
		ASSERT(pProgress);

		pProgress->SetRange32(0, 100);
		pProgress->SetPos(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

afx_msg void CSpeedDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (1 == nIDEvent)
	{
		DWORD dwElapsed = GetTickCount() - m_dwTicks;
		if (dwElapsed >= s_dwTestDuration)
			EndDialog(IDOK);
		else
		{
			CProgressCtrl* pProgress = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS);
			ASSERT(pProgress);

			pProgress->SetPos(dwElapsed * 100 / s_dwTestDuration);
		}

	}
}

void CSpeedDlg::OnDestroy()
{
	if (m_hThread)
	{
		m_bRun = false;
		//_ReadWriteBarrier();

		VERIFY(WaitForSingleObject(m_hThread, INFINITE) == WAIT_OBJECT_0);
		VERIFY(CloseHandle(m_hThread));

		m_dwTicks = GetTickCount() - m_dwTicks;
	}

	CDialog::OnDestroy();
}

DWORD WINAPI CSpeedDlg::PerfTst(PVOID pPtr)
{
	CSpeedDlg* pThis = (CSpeedDlg*) pPtr;
	ASSERT(pThis);

	size_t nCycles;
	for (nCycles = 0; ; nCycles++)
	{
		if (!pThis->m_bRun)
			break;

//		try {
			try
			{
				throw 3;
			}
			catch (...)
			{
				//throw 5;
			}
		//}
		//catch (...)
		//{
		//	volatile int nn=0;
		//}
	}

	pThis->m_nCycles = nCycles;

	return 0;
}

void CDemoDlg::OnBnClickedTstSpeed()
{
	CSpeedDlg dlg;
	if (IDOK == dlg.DoModal())
	{
		double rate = double(dlg.m_dwTicks) / double(dlg.m_nCycles) * 1000000.;

		CString sTxt;
		sTxt.Format(_T("Total cycles = %u\r\nTotal duration = %u ms\r\nSingle cycle duration = %.fns"),
			dlg.m_nCycles, dlg.m_dwTicks, rate);
		AfxMessageBox(sTxt, MB_ICONINFORMATION);

	}
}

void MyTst()
{
	__try {
		EXCEPTION_RECORD rec;
		ZeroMemory(&rec, sizeof(rec));
		rec.ExceptionCode = 0xC005321A;
		Exc::RaiseExc(rec);
	} __except(EXCEPTION_EXECUTE_HANDLER) {

	}
}

void CDemoDlg::OnBnClickedTstStopexc()
{
	MyTst();

	CString sLog;
/*
	ArticulatingObj a(sLog, _T("a"));

	try
	{
		ArticulatingObj b(sLog, _T("b"));
		try
		{
			ArticulatingObj c(sLog, _T("c"));
			throw 1;
		}
		catch (...)
		{
			ArticulatingObj g(sLog, _T("g"));
			//throw 1;
		}
		ArticulatingObj d(sLog, _T("d"));

		ArticulatingObj b1(sLog, _T("b1"));
		try
		{
			ArticulatingObj c1(sLog, _T("c1"));
			throw 1;
		}
		catch (...)
		{
			ArticulatingObj g1(sLog, _T("g1"));
			throw 1;
		}

	}
	catch (...)
	{
		ArticulatingObj e(sLog, _T("e"));
	}

	ArticulatingObj f(sLog, _T("f"));
*/

	try {


		struct InlineHandler :public Exc::Monitor {
			CString& m_sLog;
			InlineHandler(CString& sLog) :m_sLog(sLog) {}

			virtual bool Handle(EXCEPTION_RECORD* pExc, CONTEXT* pCpuCtx) {
				m_sLog += _T("I see exception, and I cancel it\r\n");
				return true;
			}
		} inlHandler(sLog);

		ArticulatingObj a(sLog, _T("A"));
		ArticulatingObj b(sLog, _T("B"));
		ArticulatingObj c(sLog, _T("C"));
		ArticulatingObj d(sLog, _T("D"));

		sLog += _T("Throwing\r\n");

		EXCEPTION_RECORD exc;
		ZeroMemory(&exc, sizeof(exc));
		exc.ExceptionCode = 0xC0012345;

		Exc::RaiseExc(exc);

	} catch (...)
	{
		sLog += _T("Caught\r\n");
	}

	sLog += _T("All finished");

	AfxMessageBox(sLog, MB_ICONINFORMATION);
}
