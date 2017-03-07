#ifndef _THREAD_H_
#define _THREAD_H_



#include "../../share/share.h"
#include "synch.h"




class __EXPORT_DLL CThread 
{
public:
	struct ThreadPara
	{
		CThread	* pThr;
		void	* pData;

		ThreadPara::ThreadPara()
		{
			pThr  = NULL;
			pData = NULL;
		}
		ThreadPara & operator = (const ThreadPara &para)
		{
			pThr = para.pThr;
			pData = para.pData;
			return *this;
		}
	};

protected:
	enum ThreadState
	{
		IDLE = 10,
		RUNNING,
		SUSPENDED,
		TERMINATED,
		FINISHED,
		DEAD,
		UNCREATED
	};
	
public:
	CThread();
	virtual ~CThread();

	void	Wait() const;
	int		Wait(DWORD timeoutMillis) const;
	
	void	SetThreadName(const char * szThrName);
	std::string GetThreadName(void);

	int		Start(void);
	int		Start(void * pD);


	void	Terminate(DWORD exitCode = 0);



	inline HANDLE		GetHandle() const;
	inline unsigned int GetCurrentThreadID() const;


	inline int			Suspend(void);
	inline void			IsSetWakeUp(bool bFlag);


	inline int			SendMsgToThread(
										IN UINT		Msg,
										IN WPARAM	wParam,
										IN LPARAM	lParam
										);

	virtual void		Quit(IN UINT Msg);
	virtual void		QuitMsg(IN UINT Msg);
	
	virtual	void		Quit(void) = 0;

	inline ThreadState	GetThreadState();

	int					IsThreadRunning();
	
protected:
	inline void			SetThreadState(ThreadState thrstate);
	
	inline int			InitCondition(
										BOOL bFlag,
										void * p,
										unsigned int nThreadID
										);
	inline void			ReleaseCondition();

private:
	int		StartFun(void * pD);
	static unsigned int __stdcall ThreadEntry(void *pV);


	//抽象类中的纯虚函数必须在继承类中实现，否则不能通过编译
	virtual int			Run(ThreadPara * p = NULL) = 0;


	// No copies do not implement
	CThread(const CThread &rhs);
	CThread &operator = (const CThread &rhs);


	void				InvalidMemberVar();


private:
	HANDLE			m_hThread;
	ThreadPara		m_threadPara;

	CCondition		m_Condition;

	unsigned int	m_uThreadID;
	ThreadState		m_EnumThrState;

	std::string		m_strThreadName;
};



#endif//_THREAD_H_