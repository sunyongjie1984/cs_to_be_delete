#ifndef _SERVERSIDE_H_
#define _SERVERSIDE_H_

#include "Socket.h"
#include "../thread/ThreadManage.h"
#include "../thread/Job.h"
#include "../thread/Thread.h"
#include "../thread/ThreadPool.h"
#include "../thread/WorkerThread.h"

//====================================================
//          class CAcceptJob                        //
//====================================================
class CAcceptJob:public CJob
{
protected:
    CAcceptSocket* acceptSock;
public:
    CAcceptJob(){acceptSock = new CAcceptSocket();}
    ~CAcceptJob(){ 
	acceptSock->Close();
	if(acceptSock!=NULL)
	    delete acceptSock;
    }

    CAcceptSocket*    GetAcceptSocket(void){
	return acceptSock;
    }
    void	SetAcceptSocket(CAcceptSocket* pSock){
	acceptSock = pSock;
    }

    virtual void  Run(void* jobdata);  
};

//====================================================
//     The base class for all server class          //
//====================================================
class CServer
{
protected:
   bool		m_ShutDown;
   CServerSocket* m_ServSocket; 
public:
   CServer(){ m_ServSocket = new CServerSocket(); }
   ~CServer(){ 
	delete m_ServSocket; 
   }

   virtual void	    Run(long lPort) = 0;
   virtual void	    ShutDown(void)=0;
};

//====================================================
//  The class for server which prefork              //
//====================================================
class CPreCreateServer:public CServer
{
private:
    CThreadManage*	m_ThreadManage;
    CAcceptJob*		m_Job;
public:
    CPreCreateServer();
    ~CPreCreateServer();
    CAcceptJob*	GetRunJob(void){return m_Job;}
    void	SetRunJob(CAcceptJob* job);

    virtual void    Run(long lPort);
    virtual void    ShutDown(void){m_ShutDown = true;}
};

#endif

