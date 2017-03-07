/*****************************************************************
*Role:The file manage Linux thread ,include create thread etc.   *
*CopyRight(c):                                                   *
*	flydish,2004,06,25                                       *
*History:                                                        *
*	Create by flydish,2004,06,25                             * 
*****************************************************************/
#ifndef _THREADMANAGE_H_
#define _THREADMANAGE_H_

#include <pthread.h>
#include "comhead.h"

typedef pthread_mutex_t		MUTEX;

//Abstract class
/*
CThread
{
public:
    CThread();
    ~CThread();
public:
    virtual CreateThread(void *(*start_routine) (void *),void *arg)=0;
    virtual DestroyThread()=0;//
    virtual SetThreadPriority()=0;
    
    virtual SetThreadProc(void* pThread)=0;
/////////////////////////////////////
    virtual int GetThreadId()=0;

///////////////////////////////////
protected:
    pthread_t 	m_pthread;//thread ;
    int		m_threadid;//thread Id

}
//
CLinPosixThread::CThread
{
public:
    CLinPosixThread();
    ~CLinPosixThread();
public:
    CreateThread(void *(*start_routine) (void *),void *arg);
    DestroyThread();//
    SetThreadPriority();
    SetThreadProc(void* pThread);

    char* GetLastError();
protected:
    pthread_t 	m_PThread;//thread ;
    int		m_ThreadId;//thread Id
    char	m_ErroStr[20];
}

CLinPosixThread::CLinPosixThread()
{
    m_pthread=0;
}

~CLinPosixThread::CLinPosixThread()
{
}

CLinPosixThread::CreateThread(void *(*start_routine) (void *),void *arg)
{
    m_pthread=pthread_create(start_routine,arg);
}
*/

/*****************************************************************
*The class is for thread pool,which likes a pool that all thread hide
*in it.When application wants to 
*****************************************************************/

CThreadPool
{
private:
    void InitAll(void);
    void DeleteAll(void);
    //void InitCriticalSection(void);
    //void DeleteCriticalSection(void);

public:
    CThreadPool();
    virtual ~CThreadPool();
    
    void SetCriThreadCount(int nCount){m_nCriThreadCount=nCount};
    int inline GetCriThreadCount(){return m_nCriThreadCount};
    
    int SetMaxThreadCount(int nMaxThreadCount) 
	{m_nMaxThreadCount=nMaxThreadCount};
    int GetMaxThreadCount(void){return m_nMaxThreadCount};

    void SetCurAllThreadCount(int nCount);
    int inline GetCurAllThreadCount(void){return m_nCurAllThreadCount};

    int inline GetCurWorkThreadCount(void){return m_nCurWorkCount};

    void inline SetLastError(int nErrorNo,char* pszErrorStr){
	pthread_mutex_lock(&pMetux);
	m_nErrorNo=nErrorNo;
	strcpy(m_pszErrorStr,pszErrorStr);		
	pthread_mutex_unlock(&pMetux);
    }
    char* inline GetLastError(int* nErrorNo){
	*nErrorNo=m_nErrorNo;
	return m_pszErrorStr;		
    }
    
protected:
    BOOL CreateNewThread(void *(*start_routine)(void *),void *arg);
    //typedef UINT (_cdecl *AFX_THREADPROC)(LPVOID);

    void IncreaseCurAllThreadCount(void);
    void DecreaseCurAllThreadCount(void);
 
    void IncreaseCurWorkThreadCount(void);
    void DecreaseCurWorkThreadCount(void);

    void IncreaseCriThreadCount(void);
    void DecreaseCriThreadCount(void);

private:
    int m_nErrorNo;
    char m_pszErrorStr[30];
    int m_nMaxThreadCount;
    int m_nCurAllThreadCount;
    int m_nCurWorkThreadCount;
    int m_nCriThreadCount;


    MUTEX pMutex;    
}

//Implement part
CThreadPool::CThreadPool(){
    InitAll();
}
~CThreadPool::CThreadPool(){
    DeleteAll();
}

void CThreadPool::InitAll()
{
    m_nErrorNo=0;
    m_nMaxThreadCount=0;
    m_nCurAllThreadCount=0;
    m_nCurWorkThreadCount=0;
    m_nCriThreadCount=0;

    pthread_mutex_init(&pMutex,PTHREAD_MUTEX_INITIALIZER);
}
void CThreadPool::DeleteAll()
{
    pthread_mutex_destroy(&pMutex);
}

//CreateNewThread
BOOL CThreadPool::CreateNewThread(void *(*start_routine)(void *),void *arg)
{
    if(m_nCurAllThreadCount>=m_nMaxThreadCount){
	return FALSE;
    }
    
    if(*start_routine==NULL)
	return FALSE;
    
    pthread_t m_pThread;
    if(pthread_create( &m_pThread, NULL,start_routine , NULL) ) {
	abort();
	return FALSE;
    }
    IncreaseCurAllThreadCount();
    
    return TRUE;
}

#endif
