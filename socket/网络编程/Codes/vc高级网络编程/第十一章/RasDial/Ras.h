// Ras.h: interface for the CRas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAS_H__4D51D463_1378_40BB_947E_AB39AF053216__INCLUDED_)
#define AFX_RAS_H__4D51D463_1378_40BB_947E_AB39AF053216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ras.h>
#pragma comment(lib, "rasapi32")

class CRasDialDlg;

class CRas : public CObject  
{
public:
	BOOL Dail(LPCTSTR entry, LPCTSTR phone, LPCTSTR user, 
				LPCTSTR pass, LPCTSTR domain);
	CRas(CRasDialDlg* dlg);
	virtual ~CRas();
	friend void WINAPI RasDialFunc(UINT, RASCONNSTATE, DWORD);

protected:
	RASDIALPARAMS	RasDialParams;
	RASCONNSTATUS	RasConnStatus;
	HRASCONN		m_hRasConn;
	CRasDialDlg*	m_dlg;
};

#endif // !defined(AFX_RAS_H__4D51D463_1378_40BB_947E_AB39AF053216__INCLUDED_)
