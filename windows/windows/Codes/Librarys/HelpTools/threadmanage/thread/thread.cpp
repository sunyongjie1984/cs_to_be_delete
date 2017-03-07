#include "thread.h"
#include "../../debuglog/debuglog.h"


CThread::CThread() : m_EnumThrState(CThread::UNCREATED)
{
	InvalidMemberVar();
}



CThread::~CThread()
{
	if (INVALID_HANDLE_VALUE != m_hThread)
	{
		::CloseHandle(m_hThread);
		InvalidMemberVar();
	}
}



void CThread::SetThreadName(const char * szThrName)
{
	m_strThreadName = szThrName;
}



std::string CThread::GetThreadName(void)
{
	return m_strThreadName;
}



int CThread::Start(void)
{
	return StartFun(NULL);
}



int CThread::Start(void * pD)
{
	return StartFun(pD);
}



int CThread::StartFun(void * pD)
{
	int nRet = __FAILED;
	
	InvalidMemberVar();
	
	if (INVALID_HANDLE_VALUE == m_hThread)
	{
		m_threadPara.pThr = reinterpret_cast<CThread *>(this);
		
		if (pD) { m_threadPara.pData = pD; }

		m_hThread = reinterpret_cast<HANDLE>(
							::_beginthreadex(
										0,
										0,
										ThreadEntry,
										reinterpret_cast<void *>(&m_threadPara),
										0,
										&m_uThreadID
										));

		if (INVALID_HANDLE_VALUE == m_hThread)
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



unsigned int __stdcall CThread::ThreadEntry(void *pV)
{	
	ThreadPara	* pT	= reinterpret_cast<ThreadPara *>(pV);
	CThread		* pThr	= reinterpret_cast<CThread *>(pT->pThr);
	int			nRet	= 0;

	pThr->SetThreadState(CThread::RUNNING);

	if (pT)
	{
		try
		{
			nRet =	pThr->Run(pT);
			pThr->SetThreadState(CThread::FINISHED);
			pThr->InvalidMemberVar();
		}
		catch(...)
		{
			Log::MsgBox(
				"CThread::ThreadEntry [%s][%p][%d] error",
				pThr->m_strThreadName.c_str(), pThr, pThr->GetCurrentThreadID()
				);

			pThr->SetThreadState(CThread::TERMINATED);
			
			return __FAILED;
		}
	}	
	return nRet;
}



void CThread::Wait() const
{
	if (!Wait(INFINITE)) { }
}



int CThread::Wait(DWORD timeoutMillis) const
{	
	int nRet = __FAILED;
	
	switch(::WaitForSingleObject(m_hThread, timeoutMillis))
	{
	case WAIT_TIMEOUT:		{ nRet = __FAILED;	break; }
	case WAIT_OBJECT_0:		{ nRet = __SUCCESS;	break; }
	default:				{ break; }	
	}	
	return nRet;
}



void CThread::Terminate(DWORD exitCode /* = 0 */)
{
	if(m_hThread)
	{
		if (!::TerminateThread(m_hThread, exitCode))
		{
			SetThreadState(CThread::TERMINATED);
			InvalidMemberVar();
			Sleep(100);
		}
	}
}




int CThread::SendMsgToThread(
								IN UINT		Msg,
								IN WPARAM	wParam,
								IN LPARAM	lParam
								)
{
	if (::PostThreadMessage(m_uThreadID, Msg, wParam, lParam))
	{
		return __SUCCESS;
	}
	return __FAILED;
}



void CThread::Quit(IN UINT Msg)
{
	CThread::ThreadState thrState = GetThreadState();

	if ((CThread::TERMINATED == thrState) || (CThread::FINISHED == thrState)
		|| (CThread::DEAD == thrState) || (CThread::UNCREATED == thrState))
	{
		return;
	}

	if (DETECT(SendMsgToThread(Msg, 0, 0)))
	{
		Log::MsgBox(
			"CThread::Quit()[%d] err[%d]", this->GetCurrentThreadID(), GetLastError()
			);

		return;
	}
}



void CThread::QuitMsg(IN UINT Msg)
{
	CThread::ThreadState thrState = GetThreadState();
	
	if ((CThread::TERMINATED == thrState) || (CThread::FINISHED == thrState)
		|| (CThread::DEAD == thrState) || (CThread::UNCREATED == thrState))
	{
		return;
	}
	
	if (DETECT(SendMsgToThread(Msg, 0, 0)))
	{
		Log::MsgBox(
			"CThread::Quit()[%d] err[%d]", this->GetCurrentThreadID(), GetLastError()
			);
		
		return;
	}
}

int CThread::IsThreadRunning()
{
	CThread::ThreadState thrState = GetThreadState();
	
	if ((CThread::RUNNING == thrState)
		|| (CThread::IDLE == thrState)
		|| (CThread::SUSPENDED == thrState))
	{
		return __SUCCESS;
	}
	return __FAILED;
}

void CThread::InvalidMemberVar()
{
	if ((CThread::TERMINATED == GetThreadState())||
		(CThread::FINISHED   == GetThreadState())||
		(CThread::UNCREATED  == GetThreadState()))
	{
		m_hThread	= INVALID_HANDLE_VALUE;
		m_uThreadID = 0;
	}
}



int CThread::InitCondition(BOOL bFlag, void * p, unsigned int nThreadID)
{
	return m_Condition.Init(bFlag, p, nThreadID);
}



void CThread::ReleaseCondition()
{
	m_Condition.Release();
}



int CThread::Suspend(void)
{
	int nRet = 0;

	if (DETECT(nRet = m_Condition.Suspend()))
	{
		SetThreadState(CThread::RUNNING);
		nRet = __SUCCESS;
	}
	else
	{
		SetThreadState(CThread::TERMINATED);
		nRet = __FAILED;
	}
	return nRet;
}



void CThread::IsSetWakeUp(bool bFlag)
{
	m_Condition.IsSetWakeUp(bFlag);
}



HANDLE CThread::GetHandle() const
{
	return m_hThread;
}



unsigned int CThread::GetCurrentThreadID() const
{
	return m_uThreadID;
}



void CThread::SetThreadState(ThreadState thrstate)
{
	m_EnumThrState = thrstate;
}



CThread::ThreadState CThread::GetThreadState()
{
	return m_EnumThrState;
}
