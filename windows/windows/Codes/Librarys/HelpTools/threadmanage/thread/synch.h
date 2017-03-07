#ifndef _SYNCH_H_
#define _SYNCH_H_



#include "../../share/share.h"



//可以同步线程和进程
class __EXPORT_DLL CSynchMutex
{
public:
	CSynchMutex();
	CSynchMutex(char * strLockName);
	virtual ~CSynchMutex();

	int WashOutSubsequently(char * strWashOut);
	
private:
	void Lock(char * strLockName);
	void Unlock();

private:
	HANDLE m_hMutex;
};





//临界区变量在进程中只能有一个。使用两个是同步将无效。
class __EXPORT_DLL CBCritical
{
public:
	CBCritical();
	virtual ~CBCritical();
	
	int Init();
	void Release();
	
	inline CBCritical &operator = (const CBCritical &para);

	void Lock();
	void Unlock();

	bool				m_bCriticalVarState;
	CRITICAL_SECTION	m_CriticalVar;
};



class __EXPORT_DLL CSynchCritical
{
public:
	CSynchCritical(CBCritical &cri);
	virtual ~CSynchCritical();

private:
	CBCritical * m_pCri;
};



class __EXPORT_DLL CSynchEvent
{
public:
	CSynchEvent(char * strLockName);
	virtual ~CSynchEvent();
	
	void Lock();
	void Unlock();

	
	int Init(char * strLockName);

protected:
	HANDLE m_hEvent;
};


class __EXPORT_DLL CCondition
{
public:
	CCondition();
	virtual ~CCondition();

	
	int Init(BOOL bFlag, void * p, unsigned int nThreadID);
	void Release();


	int Suspend();
	void IsSetWakeUp(bool bFlag);

private:
	HANDLE	m_hSuspendEvent;

};




#endif//_SYNCH_H_
