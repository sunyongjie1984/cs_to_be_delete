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
private:
    CAcceptSocket* acceptSock;
public:
    CAcceptJob(){acceptSock = new CAcceptSocket();}
    ~CAcceptJob(){ delete acceptSock;}

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
   CServerSocket* m_ServSocket; 
public:
   CServer(){ m_ServSocket = new CServerSocket(); }
   ~CServer(){ delete m_ServSocket; }

   virtual void	    Run(long lPort) = 0;
};

//====================================================
//  The class for server which prefork              //
//====================================================
class CPreCreateServer:public CServer
{
private:
    CThreadManage*    m_ThreadManage;
public:
    CPreCreateServer();
    ~CPreCreateServer();

    virtual void    Run(long lPort);
};



#endif

