#include "debuglog.h"



Log * Log::sm_pLog = NULL;



Log::Log() : m_bBeingFlag(false)
{
	m_pDebugLog = new CBFile();
}



Log::~Log()
{
	if (m_pDebugLog)
	{
		delete m_pDebugLog;
		m_pDebugLog = NULL;
	}
}



Log * Log::Instance()
{
	if (NULL == sm_pLog)
	{
		sm_pLog = new Log();
	}
	return sm_pLog;
}



void Log::Release()
{
	if (sm_pLog)
	{
		delete sm_pLog;	sm_pLog = NULL;
	}
}



int Log::Init(char * strPath)
{
	int nRet = __FAILED;

	if (m_pDebugLog)
	{
		nRet = m_pDebugLog->Init(
									strPath,
									CBFile::CREATE,//CBFile::APPEND,
									CBFile::TEXT
									);
		
		if ((DETECT(nRet))&&(false == m_bBeingFlag))
		{
			m_bBeingFlag = true;
			this->SetThreadName("Log");
			this->Start();
			//this->Wait(5);
		}
		else
		{
			nRet = __FAILED;
		}
	}
	return nRet;
}



int Log::Run(ThreadPara * p)
{
	MSG msg;
	
	while (::GetMessage(&msg, 0, 0, 0))
	{
		switch(msg.message)
		{
			case WM_DEBUG_LOG:
			{
				char * p = (char *)msg.lParam;

				if (p)
				{
					strcat(p, "\r\n");
					m_pDebugLog->Puts(p);
					delete p;	p = NULL;
				}
				break;
			}
			case WM_EXIT_LOG://WM_QUIT:
			{
				m_bBeingFlag = false;
				return __SUCCESS;
			}
			case WM_QUIT:
			{
				m_bBeingFlag = false;
				return __SUCCESS;
			}
			default:
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				break;
			}
		}
	}
	m_bBeingFlag = false;

	return __FAILED;
}



int Log::Print(char * szFormat, ...)
{
	char	* buf	= NULL;
	va_list ap		= NULL;
	int		nRet	= 0;

	va_start(ap, szFormat);

	nRet = vprintf(szFormat, ap);

	buf = new char[++nRet];
	memset(buf, 0, nRet);
	nRet = vsprintf(buf, szFormat, ap);

	va_end(ap);

	if (EOF == nRet)
	{
		nRet = __FAILED;
	}
	else
	{
		if (DETECT(Log::Instance()->SendMsgToThread(WM_DEBUG_LOG, 0, (LPARAM)buf)))
		{
			nRet = __SUCCESS;
		}
		else
		{
			nRet = __FAILED;
		}
	}
	return nRet;
}



void Log::Quit(void)
{
	CThread::Quit(WM_DEBUG_LOG);
}



/*
void va_start( va_list arg_ptr, prev_param );
type va_arg( va_list arg_ptr, type );
void va_end( va_list arg_ptr );
上述宏在stdarg.h中定义
*/

void Log::DebugStr(char * szFormat, ...)
{
	char	* buf	= NULL;
	va_list ap		= NULL;
	int		nRet	= 0;

	va_start(ap, szFormat);

	nRet = vprintf(szFormat, ap);

	buf = new char[++nRet];
	memset(buf, 0, nRet);
	nRet = vsprintf(buf, szFormat, ap);
		
	OutputDebugString(buf);
	
	delete [] buf;	buf = NULL;

	va_end(ap);
}



int Log::MsgBox(
					 IN HWND hWnd,
					 IN UINT uType,
					 IN char * szCaption,
					 IN char * szFormat,
					 ...
					 )
{
	char	* buf	= NULL;
	va_list ap		= NULL;
	int		nRet	= 0;

	va_start(ap, szFormat);

	nRet = vprintf(szFormat, ap);

	buf = new char[++nRet];
	memset(buf, 0, nRet);
	nRet = vsprintf(buf, szFormat, ap);

	nRet = ::MessageBox(hWnd, buf, szCaption, uType);
	
	delete [] buf;	buf = NULL;

	va_end(ap);

	return nRet;
}

void Log::MsgBox(IN char * szFormat, ...)
{
	char	* buf	= NULL;
	va_list ap		= NULL;
	int		nRet	= 0;

	va_start(ap, szFormat);
	
	nRet = vprintf(szFormat, ap);
	buf = new char[++nRet];
	memset(buf, 0, nRet);
	nRet = vsprintf(buf, szFormat, ap);
	
	::MessageBox(NULL, buf, "Hint", NULL);
	
	delete [] buf;	buf = NULL;

	va_end(ap);
}