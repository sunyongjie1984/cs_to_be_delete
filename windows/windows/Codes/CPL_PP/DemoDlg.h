class CDemoDlg : public CDialog
{
public:
	CDemoDlg();

protected:
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDR_APPLET1 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDemoDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDemoDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  DECLARE_DYNCREATE(CDemoDlg)
};


class CDemoPage1 : public CPropertyPage
{
public:
	CDemoPage1();
	~CDemoPage1();

protected:
	//{{AFX_DATA(CDemoPage1)
	enum { IDD = IDR_APPLET2_PAGE1 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDemoPage1)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	DECLARE_DYNCREATE(CDemoPage1)

	//{{AFX_MSG(CDemoPage1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CDemoPage2 : public CPropertyPage
{
public:
	CDemoPage2();
	~CDemoPage2();

protected:
	//{{AFX_DATA(CDemoPage2)
	enum { IDD = IDR_APPLET2_PAGE2 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDemoPage2)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	DECLARE_DYNCREATE(CDemoPage2)

	//{{AFX_MSG(CDemoPage2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CDemoPropertySheet : public CPropertySheet
{
public:
	CDemoPropertySheet();
	virtual ~CDemoPropertySheet();

protected:
  CDemoPage1 m_Page1;
  CDemoPage2 m_Page2;

	//{{AFX_VIRTUAL(CDemoPropertySheet)
	//}}AFX_VIRTUAL

	DECLARE_DYNCREATE(CDemoPropertySheet)

	//{{AFX_MSG(CDemoPropertySheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


