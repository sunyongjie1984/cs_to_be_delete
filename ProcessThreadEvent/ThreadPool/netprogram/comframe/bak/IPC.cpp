/**********************************************************************
*Role:The file define all the IPC class such as mutex,Semaphore etc.  *
*CopyRight(C):                                                        *
*                                                                     *
**********************************************************************/
#ifndef _IPC_H_
#define _IPC_H_

#include "comhead.h"
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define DIR_MODE  (FILE_MODE|S_IXUSR|S_IXGRP|S_IXOTH)

/**************************************************************************
 * The CSyncObject class is a pure virtual class that provides            * 
 * functionality common to the synchronization objects in Win32.          *
 * The Microsoft Foundation Class Library provides several classes        *
 * derived from CSyncObject. These are                                    *
 * CEvent, CMutex, CCriticalSection, and CThreadSemaphore.                      *
 *************************************************************************/

// Classes declared in this file

class CSyncObject;
    class CThreadSemaphore;
    class CThreadMutex;
    //class CCriticalSection;

//class CSingleLock;
//class CMultiLock;
class CCondition;

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

class CSyncObject
{
public:
    CSyncObject( ){}
    virtual ~CSyncObject( ){} 

    virtual int Lock  ( ) = 0;
    virtual int Unlock( ) = 0;
};

/**************************************************************************
 * All the IPC class such as CThreadxxx is only used in a process ,       * 
 * So they only is used for thread sync,if you want to sync between       *
 * server process,or server thread in different process ,you should use   *
 * the another IPC class such CProcessxxx                                 *
 *************************************************************************/

class CThreadMutex : public CSyncObject
{
    friend class CCondition;
protected:
    pthread_mutex_t      m_Mutex;
    pthread_mutexattr_t  m_MutexAttr;

public:

    CThreadMutex( ){
        pthread_mutexattr_init( &m_MutexAttr );
        pthread_mutex_init( &m_Mutex, &m_MutexAttr );
    }
    virtual ~CThreadMutex( ){
        pthread_mutexattr_destroy( &m_MutexAttr );
        pthread_mutex_destroy( &m_Mutex );
    }
    
    pthread_mutex_t* GetMutex( ) { return &m_Mutex; }

    virtual int Lock   ( ) { return pthread_mutex_lock   ( &m_Mutex ); }
    virtual int Unlock ( ) { return pthread_mutex_unlock ( &m_Mutex ); }
    virtual int Trylock ( ) { return pthread_mutex_trylock ( &m_Mutex ); }
};


class CCondition
{
protected:
    pthread_cond_t      m_Cond;
    CThreadMutex	m_Mutex;

public:
    CCondition ( ) { pthread_cond_init   ( &m_Cond, NULL ); }
    virtual ~CCondition( ) { pthread_cond_destroy( &m_Cond ); }

    void Wait( ){ 
	pthread_cond_wait( &m_Cond, m_Mutex.GetMutex());
    }

    void Signal   ( ) { pthread_cond_signal( &m_Cond )   ; }
    void Broadcast( ) { pthread_cond_broadcast( &m_Cond ); }
};

class CThreadSemaphore : CSyncObject
{
protected:
    int			m_CurValue;//the number that current used!
    int			m_MaxValue ;
    CThreadMutex	m_Mutex;
    CCondition		m_Cond;
private: 
    void Init( int maxvalue );

public:
    CThreadSemaphore(){}
    CThreadSemaphore ( int maxvalue = 1 ){ Init( maxvalue ); }
    virtual ~CThreadSemaphore( ) { }

    int GetCurValue( ) const { return m_CurValue; }
    int GetMaxValue( ) const { return m_MaxValue; }
    
    virtual int  Lock( );
    virtual int  Unlock( );
};

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
/**************************************************************************
 * All the IPC class such as CProcessxxx can be  used in different        *
 * processes , or different thread between processed. If you only         * 
 * want to snyc between different thread in same process,you can use      *
 * the class CThreadxxx                                                   *
 *************************************************************************/
class CProcessMutex : public CSyncObject
{
protected:
    int		   m_Semap;    
    struct sembuf  m_SemBuf;
    union semun {
	int 	val;
	struct semid_ds *buf;
 	USHORT	*array;
    }   m_Semun;
    int		   m_Value;	
public:
    CProcessMutex( ){
    	m_Semap = semget(GetIpcKey("IPCNAME"),1,IPC_CREAT);
    }

    CProcessMutex(char* m_pMutexName ){
   	assert(m_pMutexName != NULL);
    	m_Semap = semget(GetIpcKey(m_pMutexName),1,IPC_CREAT);
    }

    virtual ~CProcessMutex( ){}

    virtual int Lock( ) ;
    virtual int Unlock( );    
};

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

/**************************************************************************
 * The class CSingleLock and CMultiLock is used for both thread and       * 
 * process.                                                               *
 * server process,or server thread in different process ,you should use   *
 * the another IPC class such CProcessxxx                                 *
 *************************************************************************/

/***************CSingleLock******************************/
class CSingleLock
{
public:
    CSingleLock(CSyncObject* pObject, int bInitialLock = 0);
    ~CSingleLock( ){ delete m_pObject;}

    int    Lock( );
    int    Unlock( );
    int    IsLocked( ){ return m_IsLock ; }

protected:
    CSyncObject* m_pObject;
    int    m_IsLock; 
};

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

#endif

main()
{
    printf("%s\n",IPCNAME("test"));
    printf("%d\n",GetIpcKey("test"));
}
