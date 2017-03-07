// Network.h: interface for the CNetwork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORK_H__5AA3FFD5_BF97_4202_AEE7_DCC99A26A442__INCLUDED_)
#define AFX_NETWORK_H__5AA3FFD5_BF97_4202_AEE7_DCC99A26A442__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>

#include <stdio.h>

#include "winSock2.h"

#include "process.h"

#include "Regedit.h"

#pragma comment( lib, "Ws2_32" )

typedef struct _CLIENTSOCKET
{

	SOCKET receiceSocket;

}CLIENTSOCKET, *PCLIENTSOCKET;

class CNetwork  
{
public:
	CNetwork();
	virtual ~CNetwork();

public:
	int CreateReceiceThread();

	static VOID GetComputerTime( DWORD &dwTime );

	static unsigned _stdcall MsgReceiceTask( LPVOID param );

private:
	static int __InitSocket( SOCKET & socketA );

	static unsigned _stdcall __ReceiceThread( LPVOID param );
};

#endif // !defined(AFX_NETWORK_H__5AA3FFD5_BF97_4202_AEE7_DCC99A26A442__INCLUDED_)
