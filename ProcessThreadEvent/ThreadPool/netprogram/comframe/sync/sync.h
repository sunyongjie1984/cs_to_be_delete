/**********************************************************************
*Role:The file define all the IPC class such as mutex,Semaphore etc.  *
*CopyRight(C):                                                        *
*                                                                     *
**********************************************************************/
#ifndef _SYNC_H_
#define _SYNC_H_

#include "../include/comhead.h"
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

extern char* IPCNAME(const char* pCharName);
extern key_t GetIpcKey(const char* m_KeyName);

/**************************************************************************
 * The CSyncObject class is a pure virtual class that provides            * 
 * functionality common to the synchronization objects in Win32.          *
 * The Microsoft Foundation Class Library provides several classes        *
 * derived from CSyncObject. These are                                    *
 * CEvent, CMutex, CCriticalSection, and CThreadSemaphore.                *
 *************************************************************************/

// Classes declared in this file

class CSyncObject;
    class CThreadSemaphore;
    class CThreadMutex;
    //class CCriticalSection;

class CSingleLock;
//class CMultiLock;
class CCondition;

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
    //friend class CCondition;
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
    virtual int Trylock ( ){ return pthread_mutex_trylock ( &m_Mutex ); }
};

class CCondition
{
protected:
    int			m_ActiveWaiters;
    bool		m_SendSignal;
    pthread_cond_t      m_Cond;
    CThreadMutex	m_Mutex;

public:
    CCondition ( ) ;
    virtual ~CCondition( ) ;

    void Wait( );
    void WaitTimeout(int ms);

    void Signal   ( ) ;
    void SignalAll( ) ;
   
    void Lock();
    void Unlock();
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

#endif
