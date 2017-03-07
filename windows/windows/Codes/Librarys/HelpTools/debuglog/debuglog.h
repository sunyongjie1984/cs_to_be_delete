#ifndef _DEBUG_LOG_H_
#define _DEBUG_LOG_H_



#include "../threadmanage/thread/thread.h"
#include "../file/bfile.h"



class __EXPORT_DLL Log : public CThread
{
public:
	static Log	* Instance();
	static void Release();
	
	static void DebugStr(char * szFormat, ...);

	static void MsgBox(IN char * szFormat, ...);
	static int  MsgBox(
						 IN HWND hWnd,
						 IN UINT uType,
						 IN char * szCaption,
						 IN char * szFormat,
						 ...
						 );

	virtual void Quit(void);

	int Init(char * strPath);

	static int Print(char * szFormat, ...);

private:
	Log();
	virtual ~Log();

	int Run(ThreadPara * p);

private:
	CBFile		* m_pDebugLog;
	static Log	* sm_pLog;
	bool		m_bBeingFlag;
};




#endif//_DEBUG_LOG_H_