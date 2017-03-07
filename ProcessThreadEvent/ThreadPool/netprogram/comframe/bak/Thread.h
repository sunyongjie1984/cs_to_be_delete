#ifndef _THREAD_H_
#define _THREAD_H_

#include "comhead.h"
#include <semaphore.h>
#include <pthread.h>

typedef void ThreadHandler;
typedef sem_t Semaphore;


typedef enum
{
    issCreate =0,
    issIdle,
    issRunning,
    issSuspended,
    issTerminated,
    issFinished 
}ThreadState;

//define thread errocde
#define Error_ThreadSuccess		0
#define Error_ThreadInit		1
#define Error_ThreadCreate		2	
#define Error_ThreadSuspend 		3
#define Error_ThreadResume	 	4	
#define Error_ThreadCancel		5
#define Error_ThreadTerminalte		6
#define Error_ThreadExit		7
#define Error_ThreadSetPriority		8


class CThread
{
private:
    ThreadHandler   m_Handler;    
    int		m_ErrCode;
    Semaphore	m_ThreadSemaphore;	//the inner  semaphore,which is used to realize
					//the suspend operation
protected:
    unsigned long m_ThreadID;	

    bool	m_CreateSuspended;	//if suspend after creating

    char*	m_ThreadName; 
    ThreadState m_ThreadState;		//the state of the thread

    void 	SetErrcode(int errcode){m_ErrCode = errocde;}
    void	SetThreadState(ThreadState state){m_ThreadState = state;}
    
public: 
    CThread(bool createsuspended,int priority = -1);
    virtual ~CThread();

    void 	Suspend(void);		//Suspend the thread whichi is running
    void	Resume(void);		//Resume the thread which has bee suspended
    void	Terminate(void);	//Terminate the thread
    void	Sleep(void);		//Set the thread to sleep
    void	WaitFor(void);		
    
    ThreadState	GetThreadState(void){return m_ThreadState;}//Get the state of the thread 

    int		GetLastError(void){return m_ErrCode;}
    ThreadState GetThreadState(void){return m_ThreadState;}
}
#endif
