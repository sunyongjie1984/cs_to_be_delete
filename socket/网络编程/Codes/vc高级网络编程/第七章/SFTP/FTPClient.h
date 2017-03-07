// FTPClient.h: interface for the CFTPClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPCLIENT_H__C10266B9_50F4_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_FTPCLIENT_H__C10266B9_50F4_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ftpsocket.h"
#include "messagedlg.h"

class CSFTPDoc;

class CFTPClient  
{
protected:
	BOOL ReadStr2();
	int  ReadStr();
	BOOL WriteStr(CString outputstring);
	BOOL ConnectRemote(CString serverhost,int serverport);
	CArchive*		m_pCtrlRxarch;
	CArchive*		m_pCtrlTxarch;
	CSocketFile*	m_pCtrlsokfile;
	CFTPSocket*		m_Ctrlsok;


	int m_fc;
	CString m_retmsg;
	CByteArray m_buf;
	CString m_strLine;
public:
	CMessageDlg m_dlgMsg;

	Disconnect();
	BOOL MoveFile(CString remotefile, CString localfile,BOOL get,BOOL pasv = FALSE);
	BOOL List();
	BOOL FTPcommand(CString command);
	BOOL Logon(CString hostname,int hostport,CString username, CString password, CString acct, CString fwhost,CString fwusername, CString fwpassword,int fwport,int logontype);
	void Receive();
	CFTPClient(CSFTPDoc *pDoc);
	virtual ~CFTPClient();
protected:
	BOOL GetLine(int& ndx);
	void ProcessList();
	CSFTPDoc* m_pDoc;
};

#endif // !defined(AFX_FTPCLIENT_H__C10266B9_50F4_11D5_B587_00E04C39B036__INCLUDED_)
