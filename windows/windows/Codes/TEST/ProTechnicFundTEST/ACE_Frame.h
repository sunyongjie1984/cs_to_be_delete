// ACE_Frame.h: interface for the ACE_Frame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACE_FRAME_H__A1F3B371_F97E_4259_8FC2_A0449525F9BB__INCLUDED_)
#define AFX_ACE_FRAME_H__A1F3B371_F97E_4259_8FC2_A0449525F9BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ace/process_mutex.h"

#include "ace/Synch.h"

class ACE_Frame  
{
public:
	ACE_Frame();
	virtual ~ACE_Frame();

public:
	static VOID DynamicSetThreadPriority( int iPriority );
};

#include "ace/task.h"


class ACE_Task_Visit_DB : public ACE_Task_Base, public ACE_Frame
{
public:
	ACE_Process_Mutex	m_FileOpeateProcessMutex;
	
public:
	ACE_Task_Visit_DB();
	
	virtual ~ACE_Task_Visit_DB();
	

private:
	int svc();
};





/************************************************************************/
/*    Í¨Ñ¶¿ò¼Ü                                                          */
/************************************************************************/
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h"

class ACE_Request_Handler : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>,ACE_Frame
{
public:
	ACE_Request_Handler (ACE_Thread_Manager *tm = 0);

protected:
	virtual int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);
	virtual int handle_close (ACE_HANDLE fd, ACE_Reactor_Mask = 0);
private:
};

#include "ace/SOCK_Acceptor.h"
#include "ace/Acceptor.h"

typedef ACE_Strategy_Acceptor <ACE_Request_Handler, ACE_SOCK_ACCEPTOR> ACCEPTOR;


//=================================================================================
#include "ace/TP_Reactor.h"

class ACE_Server : public ACE_Frame
{
public:
	static int ServerStart();

public:
	ACE_Server();
	virtual ~ACE_Server();
};

//==================================================================================
#include "ace/SOCK_Connector.h"

#include <string>
#include <list>

using namespace std;

typedef std::list<std::string> string_list;


class HelpTools : public ACE_Frame 
{
public:
	HelpTools();
	~HelpTools();

public:
	static string_list get_server_ip( string strIp );

	static int connect( ACE_SOCK_Stream   &stream,
						const string_list &ip_list,
						const int port );

};
#endif // !defined(AFX_ACE_FRAME_H__A1F3B371_F97E_4259_8FC2_A0449525F9BB__INCLUDED_)
