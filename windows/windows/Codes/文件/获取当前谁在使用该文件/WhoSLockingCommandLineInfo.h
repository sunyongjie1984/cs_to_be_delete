// WhoSLockingCommandLineInfo.h: interface for the CWhoSLockingCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WHOSLOCKINGCOMMANDLINEINFO_H__285A038E_A959_11D3_BFE4_0010E3B966CE__INCLUDED_)
#define AFX_WHOSLOCKINGCOMMANDLINEINFO_H__285A038E_A959_11D3_BFE4_0010E3B966CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWhoSLockingCommandLineInfo : public CCommandLineInfo  
{
public:
	CString m_szDefaultFilePath;
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);
	CWhoSLockingCommandLineInfo();
	virtual ~CWhoSLockingCommandLineInfo();

};

#endif // !defined(AFX_WHOSLOCKINGCOMMANDLINEINFO_H__285A038E_A959_11D3_BFE4_0010E3B966CE__INCLUDED_)
