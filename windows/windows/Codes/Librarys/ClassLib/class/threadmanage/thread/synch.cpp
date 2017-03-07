#include "synch.h"



CSynchMutex::CSynchMutex(char * strLockName)
{
	Lock(strLockName);
}



CSynchMutex::~CSynchMutex()
{
	Unlock();
}



void CSynchMutex::Lock(char * strLockName)
{
	m_hMutex = ::CreateMutex(NULL, TRUE, strLockName);
	
	int nRet = ::GetLastError();
	if ((NULL == m_hMutex)||(ERROR_ALREADY_EXISTS == nRet))
	{
		::WaitForSingleObject(m_hMutex,INFINITE);	
	}
}



void CSynchMutex::Unlock()
{
	if(NULL != m_hMutex)
	{
		::ReleaseMutex(m_hMutex);
		
		if (NULL != m_hMutex)
		{
			::CloseHandle(m_hMutex);
		}
	}
}



int CSynchMutex::WashOutSubsequently(char * strWashOut)
{	
	m_hMutex = ::CreateMutex( NULL, TRUE, strWashOut );
	
	if ((NULL == m_hMutex)||
		(ERROR_ALREADY_EXISTS == ::GetLastError()))
	{
		return __SUCCESS;
	}
	return __FAILED;
}



CBCritical::CBCritical() : m_bCriticalVarState(false)
{
	Init();
}



CBCritical::~CBCritical()
{
	Release();
}



int CBCritical::Init()
{
	if (!m_bCriticalVarState)
	{
		InitializeCriticalSection(&m_CriticalVar);
		m_bCriticalVarState = true;
		return __SUCCESS;
	}
	return __FAILED;
}



void CBCritical::Release()
{
	if (m_bCriticalVarState)
	{
		DeleteCriticalSection(&m_CriticalVar);
		m_bCriticalVarState = false;
	}
}



CBCritical &CBCritical::operator = (const CBCritical &para)
{
	m_CriticalVar		= para.m_CriticalVar;
	m_bCriticalVarState = para.m_bCriticalVarState;
	return *this;
}


	
void CBCritical::Lock()
{
	if (m_bCriticalVarState)
	{
		EnterCriticalSection(&m_CriticalVar);
	}
}



void CBCritical::Unlock()
{
	if (m_bCriticalVarState)
	{
		LeaveCriticalSection(&m_CriticalVar);
	}
}








CSynchCritical::CSynchCritical(CBCritical &cri)
{
	m_pCri = &cri;
	
	m_pCri->Lock();
}



CSynchCritical::~CSynchCritical()
{
	m_pCri->Unlock();
}



CSynchEvent::CSynchEvent(char * strLockName)
{
	if (__FAILED == Init(strLockName)) { }

	Lock();
}



CSynchEvent::~CSynchEvent()
{
	Unlock();
}



int CSynchEvent::Init(char * strLockName)
{
	m_hEvent = ::CreateEvent(NULL,
		FALSE,	//能够告诉系统是创建一个人工重置的事件（TRUE）还是创建一个自动重置的事件（FALSE）
		TRUE,	//用于指明该事件是要初始化为已通知状态（TRUE）还是未通知状态（FALSE）
		strLockName);/*	当系统创建事件对象后，createEvent就将与进程相关的句柄返回给事件对象。
						其他进程中的线程可以获得对该对象的访问权，方法是使用在pszName参数中
						传递的相同值，使用继承性
					 */
	
	if ((NULL == m_hEvent)||
		(ERROR_ALREADY_EXISTS == ::GetLastError()))
	{
		return __FAILED;
	}
	return __SUCCESS;
}



void CSynchEvent::Lock()
{
	::WaitForSingleObject(m_hEvent, INFINITE);
}



void CSynchEvent::Unlock()
{
	if(NULL != m_hEvent)
	{
		::SetEvent(m_hEvent);
		
		if (NULL != m_hEvent)
		{
			::CloseHandle(m_hEvent);
		}
	}
}







CCondition::CCondition() : m_hSuspendEvent(NULL)
{
}



CCondition::~CCondition()
{
	Release();
}



int CCondition::Init(BOOL bFlag, void * p, unsigned int nThreadID)
{
	int nRet = __FAILED;

	if (NULL == m_hSuspendEvent)
	{
		char strLockName[128] = {0};

		sprintf(strLockName, "%p_%d", p, nThreadID);
				
		m_hSuspendEvent = ::CreateEvent(NULL, FALSE, bFlag, strLockName);

		if ((NULL == m_hSuspendEvent)||
			(ERROR_ALREADY_EXISTS == ::GetLastError()))
		{
			nRet = __FAILED;
		}
		else
		{
			nRet = __SUCCESS;
		}
	}
	return nRet;
}



void CCondition::Release()
{
	if(NULL != m_hSuspendEvent)
	{
		::CloseHandle(m_hSuspendEvent);
	}
}



int CCondition::Suspend()
{
	int nRet = __FAILED;

	switch(::WaitForSingleObject(m_hSuspendEvent, INFINITE))
	{
		case WAIT_TIMEOUT:
		{
			nRet = __FAILED;
			break;
		}
		case WAIT_OBJECT_0:
		{
			nRet = __SUCCESS;
			break;
		}
		default:
		{
			break;
		}	
	}
	return nRet;
}


void CCondition::IsSetWakeUp(bool bFlag)
{
	if (bFlag)
	{
		::ResetEvent(m_hSuspendEvent);
	}
	else
	{
		::SetEvent(m_hSuspendEvent);
	}
}
