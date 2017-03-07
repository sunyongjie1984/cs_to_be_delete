#include "Sync.h"

char* IPCNAME(const char* pCharName)
{
    char *dir="/tmp",*dst,*slash;
    if(( dst = (char*)malloc( PATH_MAX )) == NULL )
	return NULL;	
    if( dir[strlen(dir)-1] == '/')
	slash = "";
    else
	slash = "/";

    snprintf(dst,PATH_MAX,"%s%s%s",dir,slash,pCharName);

    return dst;
}

key_t GetIpcKey(const char* m_KeyName)
{
   return ftok(m_KeyName,0x53); 
}

//===========================================================
//       CCondition
//===========================================================

CCondition::CCondition()
{
    m_SendSignal = false;
    m_ActiveWaiters = 0;
    int result = 0;

    pthread_condattr_t condattrDetails;
    memset(&condattrDetails,0,sizeof(condattrDetails));

    if((result = pthread_condattr_init(&condattrDetails)) != 0)
    {
	return;
    }

    if((result = pthread_cond_init(&m_Cond, &condattrDetails)) != 0)
    {
	return;
    }

    if((result = pthread_condattr_destroy(&condattrDetails)) != 0)
    {
	return;
    }
}

CCondition::~CCondition()
{
    unsigned int retry = 0;

    while ((pthread_cond_destroy(&m_Cond) == EBUSY) && (retry <= 10))
    {
	retry++;
	SignalAll();
    }
}

void CCondition::Wait(void)
{
    m_Mutex.Lock();

    m_ActiveWaiters++;
    while (!m_SendSignal)
    {
	pthread_cond_wait(&m_Cond, m_Mutex.GetMutex());
    }

    m_ActiveWaiters--;

    if (m_ActiveWaiters == 0)
	m_SendSignal = false;

    m_Mutex.Unlock();
}

void CCondition::WaitTimeout(int ms)
{
    struct timespec timeout;
    struct timeval  tp;

    gettimeofday(&tp, NULL);

    timeout.tv_sec   = (ms / 1000) + tp.tv_sec;
    timeout.tv_nsec  = ((ms % 1000) * 1000000) + (tp.tv_usec * 1000);

    while (timeout.tv_nsec >= 1000000000)
    {
	timeout.tv_nsec -= 1000000000;
	timeout.tv_sec++;
    }

    m_Mutex.Lock();

    m_ActiveWaiters++;
    int result = 0;
    while (!m_SendSignal)
    {
	if ((result = pthread_cond_timedwait(&m_Cond, m_Mutex.GetMutex(), &timeout)) == ETIMEDOUT)
	    break;
    }
    m_ActiveWaiters--;
    if ((result == 0) && (m_ActiveWaiters == 0))
	m_SendSignal = false;

    m_Mutex.Unlock();
}

void CCondition::Signal(void)
{
    m_Mutex.Lock();
    if (!m_SendSignal)
    {
        pthread_cond_signal(&m_Cond);
        m_SendSignal = true;
    }
    m_Mutex.Unlock();
}

void CCondition::SignalAll(void)
{
   m_Mutex.Lock();
   pthread_cond_broadcast(&m_Cond);
   m_SendSignal = true;
   m_Mutex.Unlock();
}

void CCondition::Lock(void)
{
    m_Mutex.Lock();
}

void CCondition::Unlock(void)
{
    m_Mutex.Unlock();
}

//===============================================================
//              CThreadSemaphore
//===============================================================
void CThreadSemaphore::Init( int maxvalue )
{
    m_Mutex.Lock( );
    m_CurValue = 0;
    m_MaxValue = maxvalue;
    m_Mutex.Unlock( );

    m_Cond.Signal( );
}

int CThreadSemaphore::Lock( )
{
    m_Mutex.Lock( );
    while( m_CurValue >= m_MaxValue)
	m_Cond.Wait( );
    m_CurValue++;
    m_Mutex.Unlock( );

    m_Cond.Signal( );
    return m_CurValue;
}

int CThreadSemaphore::Unlock( )
{
    m_Mutex.Lock( );
    while ( m_CurValue <= 0 )
	m_Cond.Wait( );
    m_CurValue--;

    m_Mutex.Unlock( );
    m_Cond.Signal( );
    return m_CurValue;
}

//======================================================================
//                         CProcessMutex
//======================================================================

int CProcessMutex::Lock( )
{
   m_SemBuf.sem_num  = 0;
   m_SemBuf.sem_op   = -1;
   m_SemBuf.sem_flg = SEM_UNDO;

   semop(m_Semap,&m_SemBuf,1); 
}
int CProcessMutex::Unlock( )
{
   m_SemBuf.sem_num  = 0;
   m_SemBuf.sem_op   = 1;
   m_SemBuf.sem_flg = SEM_UNDO;
    
   semop(m_Semap,&m_SemBuf,1); 
}
//===================================================================
//              CSingleLock
//===================================================================

CSingleLock::CSingleLock(CSyncObject* pObject ,int bInitialLock)
{
    assert(pObject != NULL);
    m_pObject = pObject;
    
    if(bInitialLock == 0)
	Lock( );
}

int CSingleLock::Lock( )
{
    assert (m_pObject != NULL);
    m_pObject->Lock( ); 

    m_IsLock = 1;
    return m_IsLock;
}

int CSingleLock::Unlock( )
{
    assert (m_pObject != NULL);
    m_pObject->Unlock( ); 

    m_IsLock = 0;
    return m_IsLock;
}

/***************CMultiLock******************************/
/*
class CMultiLock
{
public:
    CMultiLock(CSyncObject* ppObjects[], DWORD dwCount, BOOL bInitialLock = 
FALSE);
public:
    DWORD Lock(DWORD dwTimeOut = INFINITE, BOOL bWaitForAll = TRUE,
		DWORD dwWakeMask = 0);
    BOOL Unlock();
    BOOL Unlock(LONG lCount, LPLONG lPrevCount = NULL);
    BOOL IsLocked(DWORD dwItem);

public:
    ~CMultiLock();
protected:
    HANDLE  m_hPreallocated[8];
    BOOL    m_bPreallocated[8];

    CSyncObject* const * m_ppObjectArray;
    HANDLE* m_pHandleArray;
    BOOL*   m_bLockedArray;
    DWORD   m_dwCount;
};
*/

