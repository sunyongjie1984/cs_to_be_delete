// apr_mfc_demoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "apr_mfc_demo.h"
#include "apr_mfc_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif







void CTCPSessionRecovery::remove_channel(CHANNEL * tc)
{
	if (tc)
	{
		double remove_channel_time_0, remove_channel_time_1;
		__QUERY_TICK_COUNT("remove_channel_time_0", remove_channel_time_0);
		
		//CLock<CLocker> l(*g_login_locker);
		//g_sessionManager.removeChannel(tc->channel);
		apr_socket_close(tc->channel);
		apr_pool_destroy(tc->mpchild);
		delete tc;
		tc = NULL;
		__QUERY_TICK_COUNT("remove_channel_time_1", remove_channel_time_1);
		
		LOG(8, "CTCPSessionRecovery::remove_channel remove_channel_time_0 -> remove_channel_time_1 = %.9lf", remove_channel_time_1 - remove_channel_time_0);
	}
}

void CTCPSessionRecovery::clear_recovery(void)
{
	// 	LOG(8,
	// 		"[ Login=%d ok=%d ]"
	// 		"[ Logout=%d ok=%d ]"
	// 		"[ Place=%d ok=%d ]"
	// 		"[ Cancel=%d ok=%d ]",
	// 		g_testUseCount.stpUserLogin_get, g_testUseCount.stpUserLogin_ok,
	// 		g_testUseCount.stpUserLogout_get, g_testUseCount.stpUserLogout_ok,
	// 		g_testUseCount.stpPlaceOrder_get, g_testUseCount.stpPlaceOrder_ok,
	// 		g_testUseCount.stpCancelOrder_get, g_testUseCount.stpCancelOrder_ok
	// 		);
	//g_sessionManager.recoveryRes();	
}


const char cmd_array[][1024] = 
{
	"51|rid1|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid17|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid16|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid15|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid14|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid13|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid12|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid11|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid10|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid9|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid8|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid7|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid6|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid5|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid4|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid38|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid19|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid41|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid29|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid3|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid43|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid45|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid39|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid40|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid46|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid55|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid36|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid56|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid47|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid44|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid52|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid51|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid42|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid48|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid21|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid30|000200000001|0|0\r\n",
	"51|rid19|000200000001|0|0\r\n",
	"51|rid18|000200000001|0|0\r\n",
	"51|rid22|000200000001|0|0\r\n",
	"51|rid49|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid34|000200000001|0|0\r\n",
	"51|rid35|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid50|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid20|000200000001|0|0\r\n",
	"51|rid11|000200000001|0|0\r\n",
	"51|rid29|000200000001|0|0\r\n",
	"51|rid1|000200000001|0|0\r\n",
	"51|rid7|000200000001|0|0\r\n",
	"51|rid43|000200000001|0|0\r\n",
	"51|rid37|000200000001|0|0\r\n",
	"51|rid21|000200000001|0|0\r\n",
	"51|rid53|000200000001|0|0\r\n",
	"51|rid57|000200000001|0|0\r\n",
	"51|rid50|000200000001|0|0\r\n",
	"51|rid23|000200000001|0|0\r\n",
	"51|rid59|000200000001|0|0\r\n",
	"51|rid22|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"21|000200000001|6|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|8|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|9|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|10|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|11|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|12|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|13|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"51|rid15|000200000001|0|0\r\n",
	"51|rid17|000200000001|0|0\r\n",
	"25|16|2143|a\r\n",
	"51|rid42|000200000001|0|0\r\n",
	"21|000200000001|17|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|18|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|19|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|20|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|21|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"51|rid35|000200000001|0|0\r\n",
	"51|rid4|000200000001|0|0\r\n",
	"21|000200000001|24|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|25|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|27|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|28|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|29|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|30|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|31|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|32|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|33|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|34|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"51|rid26|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid58|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"51|rid3|000200000001|0|0\r\n",
	"51|rid9|000200000001|0|0\r\n",
	"51|rid16|000200000001|0|0\r\n",
	"51|rid2|000200000001|0|0\r\n",
	"51|rid39|000200000001|0|0\r\n",
	"51|rid36|000200000001|0|0\r\n",
	"51|rid57|tcp://dfitc.com|2030|000200000001|***|false||\r\n",
	"21|000200000001|40|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|41|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|42|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|43|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|44|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|45|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|46|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n",
	"21|000200000001|47|a1305|4922.0|1|1|0|1|1|0|2300.0|1|0|stp\r\n"
};


// 
// extern __PRINT g_printf_func;
// extern int g_log_print_level;
// 
// extern __PRINTX g_printf_func_x;
// extern int g_log_print_level_x;
// 
// void print0(char * s)
// {
// 	printf("%s\r\n", s);
// }
// 
// 
// void print1(char * s)
// {
// 	strcat(s, "\r\n");
// 	OutputDebugString(s);
// }

CListBox * g_listbox = NULL;

void print_listbox(char * s)
{
	if(g_listbox)
	{
		g_listbox->InsertString(0, s);
	}
}


static void clear_channel_tree(void * task, void * data)
{
	CChannelManager * su = (CChannelManager *)data;
	if (task)
	{
		apr_socket_t * channel = (apr_socket_t*)task;
		apr_socket_shutdown(channel, APR_SHUTDOWN_READWRITE);
		su->recovery(channel);
	}
}




/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApr_mfc_demoDlg dialog

CApr_mfc_demoDlg::CApr_mfc_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CApr_mfc_demoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CApr_mfc_demoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_task_manager = NULL;
	m_session = NULL;
	m_shineUpon = NULL;
	apr_initialize();
	apr_pool_create(&mp, NULL);
}

CApr_mfc_demoDlg::~CApr_mfc_demoDlg()
{
	if (mp)
	{
		apr_pool_destroy(mp);
		mp = NULL;
	}
	apr_terminate();
}

void CApr_mfc_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApr_mfc_demoDlg)
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CApr_mfc_demoDlg, CDialog)
	//{{AFX_MSG_MAP(CApr_mfc_demoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_THREAD_POOL_START, OnThreadPoolStart)
	ON_COMMAND(ID_THREAD_POOL_STOP, OnThreadPoolStop)
	ON_COMMAND(ID_THREAD_POOL_TEST, OnThreadPoolTest)
	ON_COMMAND(ID_CLEAR_LIST, OnClearList)
	ON_COMMAND(ID_SESSION_START, OnSessionStart)
	ON_COMMAND(ID_SESSION_STOP, OnSessionStop)
	ON_COMMAND(ID_SESSION_CONNECTOR, OnSessionConnector)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApr_mfc_demoDlg message handlers






BOOL CApr_mfc_demoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_menu.LoadMenu(IDR_MY_MENU);
	SetMenu(&m_menu);

	apr_err_print(0, 730058, "");

	if (!out2_create("test.log"))
		return FALSE;

	set_log_out_conf(-1, __win_outputdebugstr);

	g_listbox = &m_listbox;

	LOG(1, "demo start");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CApr_mfc_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CApr_mfc_demoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CApr_mfc_demoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CApr_mfc_demoDlg::OnThreadPoolStart() 
{
	// TODO: Add your command handler code here
	m_task_manager = new CTaskManager();
	m_task_manager->create(mp, 10, 50);
}

void CApr_mfc_demoDlg::OnThreadPoolStop() 
{
	// TODO: Add your command handler code here
	if (m_task_manager)
		m_task_manager->stop();

	CRITICAL_SECTION sec;

	
#if 1
	if (m_shineUpon)
		m_shineUpon->clear(clear_channel_tree, (void *)m_shineUpon);

	if (m_session)
		if (m_session->get_acceptor())
			apr_socket_close(m_session->get_acceptor());
#endif//0

#if 1
	if (m_task_manager)
		m_task_manager->stop();
#endif//0

	if (m_task_manager)
	{
		m_task_manager->join();
		
		delete m_task_manager;
		m_task_manager = NULL;
	}
#if 1
	if (m_shineUpon)
	{
		delete m_shineUpon;
		m_shineUpon = NULL;
	}
#endif//0
}



class CTestPool : public CAbstractTask
{
public:
	CTestPool(CListBox &listbox)
	{
		m_listbox = &listbox;
	}
	
	virtual ~CTestPool(){}
	
	void start(void * data)
	{
		while (!check_interrupt_request())
		{
			for (int i=0; ; i++)
			{
				if (i / 100)
				{
					i = 0;
					break;
				}
				double t;
				__QUERY_TICK_COUNT("m_d0_=", t)
					CTestTask * p = new CTestTask(*m_listbox);
				
				__QUERY_TICK_COUNT("m_d1_=", p->m_d1_)
					
					p->m_d0_ = t;
				__QUERY_TICK_COUNT("m_d2_=", p->m_d2_)
					
					p->m_task_index = i;
				__QUERY_TICK_COUNT("m_d3_=", p->m_d3_)
					m_manager->dispatch(p);
			}
			apr_sleep(8 * APR_USEC_PER_SEC);
		}
	}
	CListBox * m_listbox;
};


void CApr_mfc_demoDlg::OnThreadPoolTest() 
{
	CAbstractTask * p = new CTestPool(m_listbox);
	
	m_task_manager->dispatch(p);

	return;

	// TODO: Add your command handler code here
	while (true)
	{
		for (int i=0; ; i++)
		{
			if (i / 100)
			{
				i = 0;
				break;
			}
			double t;
			__QUERY_TICK_COUNT("m_d0_=", t)
				CTestTask * p = new CTestTask(m_listbox);
			
			__QUERY_TICK_COUNT("m_d1_=", p->m_d1_)
				
				p->m_d0_ = t;
			__QUERY_TICK_COUNT("m_d2_=", p->m_d2_)
				
				p->m_task_index = i;
			__QUERY_TICK_COUNT("m_d3_=", p->m_d3_)
				m_task_manager->dispatch(p);
		}
		apr_sleep(8 * APR_USEC_PER_SEC);
	}
}

void CApr_mfc_demoDlg::OnClearList()
{
	for (int len = m_listbox.GetCount(); len > 0; len--)
		m_listbox.DeleteString(len-1);
}

void CApr_mfc_demoDlg::OnSessionStart()
{
	m_shineUpon = new CChannelManager();
	m_shineUpon->create(mp);

	m_session = new CTCPSessionTask(m_shineUpon);
	m_task_manager->dispatch(m_session);

	CAbstractTask * pt = new CRecoveryTask(m_shineUpon);
	m_task_manager->dispatch(pt);
}

void CApr_mfc_demoDlg::OnSessionStop()
{
	if (m_shineUpon)
		m_shineUpon->clear(clear_channel_tree, (void *)m_shineUpon);
		
	if (m_session->get_acceptor())
		apr_socket_close(m_session->get_acceptor());
}


class CConnectorTask : public CAbstractTask
{
public:
	CConnectorTask(char * ip)
	{
		m_ip = ip;
	}
	virtual ~CConnectorTask()
	{
		
	}
	
	//定时清理线程
	void start(void * data)
	{
		apr_socket_t	* connector = NULL;
		apr_status_t	rv	= APR_SUCCESS;

		for (int i = 0; !check_interrupt_request(); i++)
		{
			rv = TCPConnector_create(m_manager->get_pool(), m_ip.c_str(), 10910, &connector);
			
			if (APR_SUCCESS != rv)
			{
				apr_err_print(5, rv, "");
				
				if (connector)
				{
					apr_socket_close(connector);
					connector = NULL;
				}
				if (!check_interrupt_request())
					apr_sleep(1000*1000*10);
				continue;
			}
			
			for (int k=0; k<5 && !check_interrupt_request(); k++)
			{
				int array_len = sizeof(cmd_array)/(sizeof(char)*1024);
				for (int j=0; j < array_len && !check_interrupt_request(); j++)
				{
					apr_size_t len = strlen(cmd_array[j]);
					if (APR_SUCCESS != (rv = apr_socket_send(connector, cmd_array[j], &len)))
					{
						printf("apr_socket_send failed");
						apr_sleep(APR_USEC_PER_SEC);
					}
					else
					{
						//printf("[%s][%.8d]\n", cmd_array[j], len);
					}
				}
			}
			
			apr_socket_shutdown(connector, APR_SHUTDOWN_READWRITE);
			
			if (connector)
			{
				apr_socket_close(connector);
				connector = NULL;
			}
			if (!check_interrupt_request())
				apr_sleep(APR_USEC_PER_SEC*10);
		}
	}
protected:
	std::string m_ip;
};

#include "ConfigConnectorTestDlg.h"

void CApr_mfc_demoDlg::OnSessionConnector() 
{
	// TODO: Add your command handler code here

	CConfigConnectorTestDlg dlg;
	dlg.DoModal();

	for (int i =0; i < 1; i++)
	{
		CAbstractTask * pt = new CConnectorTask(dlg.m_ipAddr.GetBuffer(0));
		m_task_manager->dispatch(pt);
	}
}
