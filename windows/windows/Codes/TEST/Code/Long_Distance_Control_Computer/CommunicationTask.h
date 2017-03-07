// CommunicationTask.h: interface for the CCommunicationTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNICATIONTASK_H__94A471FD_2048_4A66_BBE8_77CD0A4D5B77__INCLUDED_)
#define AFX_COMMUNICATIONTASK_H__94A471FD_2048_4A66_BBE8_77CD0A4D5B77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ShareResource.h"

class CCommunicationTask  
{
public:
	BOOL	StartNetWorkListenTask();

public:

	static unsigned __stdcall ReceiveControlMsgTask(
										IN			 LPVOID     param );

	static		int			  InitializeSocket( 
										IN    OUT	 SOCKET	   &communicationSocket,
										IN			 u_short	dwCommunicationPort,
										IN			 PCHAR		lpIpAddress   );

public:

	CCommunicationTask();

	virtual   ~CCommunicationTask();

private:

	static unsigned __stdcall __RunNetWorkListenTask(
												IN    LPVOID param );

};

#endif // !defined(AFX_COMMUNICATIONTASK_H__94A471FD_2048_4A66_BBE8_77CD0A4D5B77__INCLUDED_)
