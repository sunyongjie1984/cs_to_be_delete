// CUserDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CUser.h"
#include "CUserDlg.h"
#include ".\cuserdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCUserDlg ダイアログ



CCUserDlg::CCUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCUserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCUserDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCUserDlg メッセージ ハンドラ

BOOL CCUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CCUserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CCUserDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CCUserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "..\TestDll\TestDll\TestDll.h"

void CCUserDlg::OnBnClickedOk()
{
//	CTestDllApp tdllapp;

	//声明DLL函数
	typedef void (_cdecl *GETHOSTNAME)(LPTSTR strHostName);
	typedef void (_cdecl *GETSYSTEMTYPE)(char * strSystemType);
	typedef void (_cdecl *GETIPADDRESSLIST)(char ** lpIPList,DWORD *lpNumber);

	//声明函数句柄
	HMODULE hTestDLL = NULL;
	GETHOSTNAME GetHostName = NULL;
	GETSYSTEMTYPE GetSystemType = NULL;
	GETIPADDRESSLIST GetIpAddressList = NULL;

	// 加????接?
	hTestDLL = LoadLibrary("D:\\test\\TestDll\\TestDll\\Debug\\TestDLL.dll");
	if(hTestDLL == NULL)\
	{
		printf("cannot load LCDDLL.dll\n");
		exit(0);
	}

	/*** 找到?个函数的入口 ****/
	//系?名称
	GetHostName = (GETHOSTNAME)GetProcAddress(hTestDLL,"GetHostName");
	if(GetHostName==NULL)
	{
		printf("cannot load process GetHostName\n");
		FreeLibrary(hTestDLL);
		exit(1);
	}

	//操作系??型
	GetSystemType = (GETSYSTEMTYPE)GetProcAddress(hTestDLL,"GetSystemType");
	if(GetSystemType==NULL)
	{
		printf("cannot load process GetSystemType\n");
		FreeLibrary(hTestDLL);
		exit(1);
	}

	//IP地址列表
	GetIpAddressList = (GETIPADDRESSLIST)GetProcAddress(hTestDLL,"GetIPAddressList");
	if(GetSystemType==NULL)
	{
		printf("cannot load process GetIpAddressList\n");
		FreeLibrary(hTestDLL);
		exit(1);
	}

	/*** 使用LPTSTR和使用char*定?的效果是一?的 ***/

	//取机器名称
	LPTSTR szHostName = new char[1024];
	(*GetHostName)(szHostName);

	//取操作系??型
	char* szSystemType = new char[1024];
	(*GetSystemType)(szSystemType);

	//IP Address List
	DWORD ipListNumber = 0;
	//声明方式一
	//LPTSTR* lpAddress = new LPTSTR[256];
	//声明方式二
	char** lpAddress = new char*[256];
	for(int i=0;i<256;i++)
	{
		lpAddress[i] = NULL;
	}
	(*GetIpAddressList)(lpAddress,&ipListNumber);

	//?示在界面
//	m_setHostName.SetWindowText(szHostName);
//	m_setSystemType.SetWindowText(szSystemType);

	//将IP添加到list 中
	for(DWORD i=0;i < ipListNumber;i++)
	{
//		m_IPList.AddString(lpAddress[i]);
	}

//	OnOK();
}
