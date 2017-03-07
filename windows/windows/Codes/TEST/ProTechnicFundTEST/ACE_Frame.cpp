// ACE_Frame.cpp: implementation of the ACE_Frame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "ACE_Frame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "ace/ace.h" // 添加初始化

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ACE_Frame::ACE_Frame()
{
	ACE::init(); //初始化ACE,否则启线程报错
}

ACE_Frame::~ACE_Frame()
{
	
}

VOID ACE_Frame::DynamicSetThreadPriority( int iPriority )
{
	int iPri = GetThreadPriority( GetCurrentThread() );
	
	SetThreadPriority( GetCurrentThread(), iPri+iPriority );        //提高优先级
}


ACE_Task_Visit_DB::ACE_Task_Visit_DB()
{

}

ACE_Task_Visit_DB::~ACE_Task_Visit_DB()
{

}

int ACE_Task_Visit_DB::svc()
{	
/*
	while ( true )
	{
		DWORD dwWait = WaitForSingleObject( TestGlobalVariableHandle(), 0 );
		
		if( WAIT_OBJECT_0 == dwWait )
		{
			break;
		}
	}
*/
	CVisitDatabaseInterface * pVisitDB = CVisitDatabaseInterface::Instance();
	
	if ( NULL == pVisitDB )
	{
		return -1;
	}
	
	DWORD dwTestCount = 0;
	DWORD dwTest      = 0;
	CFileAuditLogInfo auditRecord;
	
	if ( -1 == pVisitDB->ReadRecordFromDatabase(
											dwTestCount,
											auditRecord,
											dwTest ) )
	{
		return -1;
	}
	pVisitDB->Test_RecordSetPro( pVisitDB->m_pRecord );

	return 0;
}



/************************************************************************/
/*                                                                      */
/************************************************************************/
ACE_Request_Handler::ACE_Request_Handler (ACE_Thread_Manager *thr_mgr)
			: ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH> (thr_mgr)
{
	this->reactor ( ACE_Reactor::instance () );
}

int ACE_Request_Handler::handle_input ( ACE_HANDLE fd )
{
	CHAR szRecvHeader[1024] = {0};

	ssize_t result = peer().recv_n( szRecvHeader, (sizeof(char) * 1024), 0);
	
	if(result > 0)
	{
		::MessageBox( NULL, szRecvHeader, "", MB_OK );
	}
	else
	{
		int error = ACE_OS::last_error();
		char szTempErr[1024] = {0};
		sprintf( szTempErr, "%d", error );
		::MessageBox( NULL, szTempErr, "recv fail", MB_OK );
	}
	
	return -1;
}

int ACE_Request_Handler::handle_close ( ACE_HANDLE fd, ACE_Reactor_Mask )
{
	return 0;
}

//=========================================================================
ACE_Server::ACE_Server()
{
	
}

ACE_Server::~ACE_Server()
{

}

static int reactor_event_hook (ACE_Reactor *)
{
	ACE_DEBUG ((LM_DEBUG,
		"(%t) handling events ....\n"));
	
	return 0;
}

static ACE_THR_FUNC_RETURN svr_worker (void *)
{
	// Server thread function.
	int result =
		ACE_Reactor::instance ()->run_reactor_event_loop (&reactor_event_hook);
	
	if (result == -1)
	{
		ACE_ERROR_RETURN ( (LM_ERROR,
					       "(%t) %p\n",
						   "Error handling events"),
						   0);
	}

	ACE_DEBUG ( (LM_DEBUG,
				"(%t) I am done handling events. Bye, bye\n") );
	
	return 0;
}

int ACE_Server::ServerStart()
{
	ACE::init(); //初始化ACE,否则启线程报错
	
	ACE_TP_Reactor	sr;
	ACE_Reactor		new_reactor ( &sr );
	
	ACE_Reactor::instance ( &new_reactor );

	ACCEPTOR		acceptor;
	ACE_INET_Addr	accept_addr (SERVER_PORT);

	if ( -1 == acceptor.open (accept_addr) )
	{
		ACE_ERROR_RETURN ( (LM_ERROR,
						   ACE_TEXT ("%p\n"),
						   ACE_TEXT ("open")),
						   1 );
	}

	ACE_Thread_Manager::instance ()->spawn_n ( 10, svr_worker );
	
	ACE_Thread_Manager::instance ()->wait ();

	return 0;
}



/************************************************************************/
/*                                                                      */
/************************************************************************/
HelpTools::HelpTools()
{

}

HelpTools::~HelpTools()
{

}


string_list HelpTools::get_server_ip( string strIp )
{
	string_list ip;

	char szServerIP[MAXHOSTNAMELEN] = {0};

#ifdef _DEBUG
	strcpy( szServerIP, strIp.c_str() );
#else

#endif

	ip.push_back(szServerIP);	

	return ip;
}


int HelpTools::connect(ACE_SOCK_Stream& stream,const string_list &ip_list,const int port)
{
	ACE_SOCK_Connector connect;

	string_list::const_iterator begin	= ip_list.begin();
	string_list::const_iterator end		= ip_list.end();

	int ret = -1;

	while(begin != end)
	{
		ACE_INET_Addr addr (port,begin->c_str());

		if (connect.connect (stream, addr) == -1)
		{
			ACE_ERROR_RETURN ( (LM_ERROR,
							   "(%t) %p Error while connecting\n",
							   "connect"),
							   -1 );
		}
		else
		{
			ret = 0;
		}

		begin++;
	}

	return ret;
}
