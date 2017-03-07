#ifndef _THREAD_H_
#define _THREAD_H_

#include "../include/comhead.h"
#include <semaphore.h>
#include <pthread.h>
//#include "ThreadPool.h"

typedef sem_t Semaphore;

typedef enum
{
    THREAD_IDLE =0,
    THREAD_RUNNING,
    THREAD_SUSPENDED,
    THREAD_TERMINATED,
    THREAD_FINISHED,
    THREAD_DEAD
}ThreadState;

//define thread errocde
#define Error_ThreadSuccess		0
#define Error_ThreadInit		1
#define Error_ThreadCreate		2	
#define Error_ThreadSuspend 		3
#define Error_ThreadResume	 	4	
#define Error_ThreadTerminated		5
#define Error_ThreadExit		6	
#define Error_ThreadSetPriority		7
#define Error_ThreadWakeup		8
#define Error_ThreadYield		9
#define Error_ThreadDetach		10
#define Error_ThreadJoin		11


class CThread
{
private:
    int		m_ErrCode;
    Semaphore	m_ThreadSemaphore;	//the inner  semaphore,which is used to realize
    unsigned long m_ThreadID;	
    bool	m_Detach;		//The thread is detached
    bool	m_CreateSuspended;	//if suspend after creating
    char*	m_ThreadName; 
    ThreadState m_ThreadState;		//the state of the thread
					//the suspend operation
protected:
    void 	SetErrcode(int errcode){m_ErrCode = errcode;}

    static void* ThreadFunction(void*);
    
public: 
    CThread();
    CThread(bool createsuspended,bool detach);
    virtual ~CThread();
    virtual void Run(void) = 0;
    void	SetThreadState(ThreadState state){m_ThreadState = state;}

    bool	Terminate(void);	//Terminate the thread

    bool	Start(void);		//Start to execute the thread
    void	Exit(void);
    bool	Wakeup(void);
    
    ThreadState	GetThreadState(void){return m_ThreadState;}//Get the state of the thread 
    int		GetLastError(void){return m_ErrCode;}
    void	SetThreadName(char* thrname){strcpy(m_ThreadName,thrname);}
    char*	GetThreadName(void){return m_ThreadName;}

    int		GetThreadID(void){return m_ThreadID;}

    int		GetThreadId(void){return m_ThreadID;}

    bool	SetPriority(int priority);
    int		GetPriority(void);

    int		GetConcurrency(void);
    void	SetConcurrency(int num);
    bool	Detach(void);
    bool	Join(void);
    bool	Yield(void);
    int		Self(void);
};
#endif
