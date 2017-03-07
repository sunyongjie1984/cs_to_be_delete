#ifndef _SYNCH_H_
#define _SYNCH_H_



#include "../../share/share.h"



class __EXPORT_DLL CSynchMutex
{
public:
	CSynchMutex(char * strLockName);
	virtual ~CSynchMutex();

	int				WashOutSubsequently(char * strWashOut);
	
private:
	void			Lock(char * strLockName);
	void			Unlock();

private:
	HANDLE m_hMutex;
};


class __EXPORT_DLL CBCritical
{
public:
	CBCritical();
	virtual ~CBCritical();

	inline CBCritical &operator = (const CBCritical &para);
	
	int					Init();
	void				Release();

	void				Lock();
	void				Unlock();

public:
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
	
	void		Lock();
	void		Unlock();

	int			Init(char * strLockName);

protected:
	HANDLE		m_hEvent;
};


class __EXPORT_DLL CCondition
{
public:
	CCondition();
	virtual ~CCondition();

	
	int			Init(BOOL bFlag, void * p, unsigned int nThreadID);
	void		Release();


	int			Suspend();
	void		IsSetWakeUp(bool bFlag);

private:
	HANDLE	m_hSuspendEvent;

};


#endif//_SYNCH_H_
