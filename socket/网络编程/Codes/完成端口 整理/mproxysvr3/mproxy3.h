#if !defined(_MPROXY3_H)
#define _MPROXY3_H
#if _MSC_VER > 1000
#pragma once
#endif

class CMProxy3
{
public:
	CMProxy3(int nListenPort ,const char * pAddr2 = NULL, int nPort2 = 0);
	~CMProxy3();
	void Start();
	void Stop();
	enum
	{
		RUNNIG,
		STOP
	}STATE;
protected:
	int m_nListenPort;
	char m_Addr2[100];
	int m_nPort2;
	HANDLE m_hThread;
	HANDLE m_hCompletionPort;
	int m_nThreadState;
	friend DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);
	friend DWORD WINAPI MProxy3Thread(LPVOID pArgu);
};


#endif
