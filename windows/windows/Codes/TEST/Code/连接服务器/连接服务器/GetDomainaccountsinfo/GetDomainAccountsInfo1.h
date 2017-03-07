// GetDomainAccountsInfo1.h: interface for the GetDomainAccountsInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETDOMAINACCOUNTSINFO1_H__74D10112_5ED7_4721_B9C6_993D3C556216__INCLUDED_)
#define AFX_GETDOMAINACCOUNTSINFO1_H__74D10112_5ED7_4721_B9C6_993D3C556216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Winnetwk.h"
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>
#include "Lmaccess.h"
#include "StdString.h"
#include <vector>
#pragma comment(lib,"Mpr.lib")
#pragma comment(lib,"ActiveDS.lib")
#pragma comment(lib,"Netapi32.lib ")

using namespace std;
typedef std::vector<CStdString> CStdStringVector;

class GetDomainAccountsInfo  
{
public:
	CStdStringVector m_strVector;
public:
	void GetAccountsinfo(CStdString serverName,CStdString groupname);
	BOOL ConnectNetword(CStdString m_serverName,CStdString lpPassword,CStdString lpUsername);
	GetDomainAccountsInfo();
	virtual ~GetDomainAccountsInfo();

	

};

#endif // !defined(AFX_GETDOMAINACCOUNTSINFO1_H__74D10112_5ED7_4721_B9C6_993D3C556216__INCLUDED_)
