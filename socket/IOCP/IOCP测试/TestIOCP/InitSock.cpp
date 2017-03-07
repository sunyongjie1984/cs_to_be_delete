// InitSock.cpp: implementation of the CInitSock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InitSock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInitSock::CInitSock()
{
	WSADATA wsaData;
	BYTE majorVer = 2, minorVer = 2; 
	WORD SockVersion = MAKEWORD(minorVer, majorVer);
	if (::WSAStartup(SockVersion, &wsaData) != 0)
	{
		exit(0);
	}
}

CInitSock::~CInitSock()
{
	::WSACleanup();
}
