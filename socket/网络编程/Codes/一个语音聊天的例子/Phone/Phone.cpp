// Phone.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Phone.h"

#include "DataEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp

BEGIN_MESSAGE_MAP(CPhoneApp, CWinApp)
	//{{AFX_MSG_MAP(CPhoneApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp construction

CPhoneApp::CPhoneApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CPhoneApp object

CPhoneApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp initialization

BOOL CPhoneApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}

//
//自定义变量
//
//全局变量
CString RemoteHost;
long RemotePort;
HWAVEOUT hWaveOut;
bool m_Opened;
WAVEHDR WaveHdrOut[MAXWAVEBLOCK];
//局部变量
static WAVEHDR WaveHdrIn[MAXWAVEBLOCK];
static char WaveOutBuffer[MAXWAVEBLOCK][MAXWAVEBUFFER];//保存播音数据用内存块
static char WaveInBuffer[MAXWAVEBLOCK][MAXWAVEBUFFER];//记录录音数据用内存块
static HWAVEIN hWaveIn;
static CExchange* m_pChange;


static void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, WORD dwInstance,
						 WAVEHDR* dwParam1, DWORD dwParam2)
{
	long result;
	char buffer[MAXWAVEBUFFER];
	long buf_len;

	switch(uMsg)
	{//判断回调类型
	case WIM_OPEN:
		//录音设备正常打开时，触发该事件
		//MessageBox(NULL,"Open success", "提示", MB_OK);
		break;
	case WIM_CLOSE:
		//录音设备正常关闭时，触发该事件
		//MessageBox(NULL,"Close success", "提示", MB_OK);
		break;
	case WIM_DATA:
		//录音设备返回数据时，触发该事件
		if(!waveInUnprepareHeader(hwi, dwParam1,sizeof(WAVEHDR)))
		{//可以释放内存。有的情况虽然返回数据，但不能释放内存，
		 //如使用同一个WAVEHDR增加多个内存块时，会出现上述情况
			memcpy(buffer, dwParam1->lpData , MAXWAVEBUFFER);//复制返回数据
			buf_len = dwParam1->dwBytesRecorded;//记录录音数据长度
			dwParam1->dwUser=0;//恢复设置
			dwParam1->dwBufferLength=MAXWAVEBUFFER;
			dwParam1->dwFlags=0;
			if(m_Opened)
			{//录音仍在继续
				result=waveInPrepareHeader(hwi,dwParam1,sizeof(WAVEHDR));
 				result=waveInAddBuffer(hwi,dwParam1,sizeof(WAVEHDR));
			}
		}
		if(buf_len > 0 && buf_len <= MAXWAVEBUFFER)
		{//有录音数据
			//发送录音数据
			m_pChange->SendTo(buffer, buf_len, RemotePort, LPCTSTR(RemoteHost));
		}
		break;
	}
};


void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, WORD dwInstance,
						 WAVEHDR* dwParam1, DWORD dwParam2)
{
	switch(uMsg)
	{//判断回调类型
	case WOM_OPEN:
		//播音设备正常打开时，触发该事件
		//MessageBox(NULL,"Open success",NULL,MB_OK);
		break;
	case WOM_CLOSE:
		//播音设备正常关闭时，触发该事件
		//MessageBox(NULL,"Close success",NULL,MB_OK);
		break;
	case WOM_DONE:
		//内存播放完成时，触发该事件
		if(!waveOutUnprepareHeader(hwo, dwParam1, sizeof(WAVEHDR)))
		{
			//delete dwParam1->lpData;//删除语音数据内存
			//delete dwParam1;//删除结构定义内存
			m_pChange->DelDataBlock();//减少内存数量记数
		}
		break;
	}
};

long _stdcall StartPhone(char* HostAddress, long lPort, long rPort) 
{
	// TODO: Add your dispatch handler code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	long sta;
	int i;
	void _stdcall ClosePhone();

	if(m_Opened)
	//设备正在使用
		return -1;
	m_Opened = true;

	if(!strlen(HostAddress))
	//无主机地址
		return -2;
	else
	{
		RemoteHost = HostAddress;//保存主机地址
		RemotePort = rPort;//保存主机端口号
	}

	m_pChange = new CExchange;//创建Socket类，UDP套接字
	if(!m_pChange->Create(lPort, SOCK_DGRAM, FD_READ|FD_WRITE|FD_OOB))
	{//套接字创建失败
		return -3;
	}

	WAVEFORMATEX waveFormatEx;
		waveFormatEx.cbSize=0;
		waveFormatEx.nAvgBytesPerSec=16000;
		waveFormatEx.nBlockAlign=2;
		waveFormatEx.nChannels=1;
		waveFormatEx.nSamplesPerSec=8000;
		waveFormatEx.wBitsPerSample=16;
		waveFormatEx.wFormatTag=WAVE_FORMAT_PCM;

	//打开播音设备并开始播音
	for(i=0;i < MAXWAVEBLOCK; i++)
		WaveHdrOut[i].lpData=WaveOutBuffer[i];//设置播音数据内存区
	hWaveOut = NULL;
	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormatEx, (unsigned long)waveOutProc, 0L, CALLBACK_FUNCTION)) 
	{//播音设备打开失败，播音设备被其他程序占用
		ClosePhone();
		return 1;
	}

	hWaveIn = NULL;
	if(sta=waveInOpen(&hWaveIn, WAVE_MAPPER, &waveFormatEx, (unsigned long)waveInProc, 1L, CALLBACK_FUNCTION)) 
	{//录音设备打开失败，可能声卡不支持全双工。
		ClosePhone();
		return 2;
	}
	
	for(i=0;i < MAXWAVEBLOCK; i++)
	{//增加录音内存
		WaveHdrIn[i].lpData=WaveInBuffer[i];
		WaveHdrIn[i].dwBufferLength=MAXWAVEBUFFER;
		WaveHdrIn[i].dwFlags=0;
		WaveHdrIn[i].dwUser=0;
		if(waveInPrepareHeader(hWaveIn, &WaveHdrIn[i], sizeof(WAVEHDR)))
		{//无法锁定该内存
			ClosePhone();
			return 3;
		}; 
		if(waveInAddBuffer(hWaveIn,&WaveHdrIn[i],sizeof(WAVEHDR)))
		{//无法增加该内存
			ClosePhone();
			return 4;
		}
	}
	if(waveInStart(hWaveIn))
	{//无法开始录音
		ClosePhone();
		return 5;
	}

	return 0;
}

void _stdcall ClosePhone() 
{
	// TODO: Add your dispatch handler code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Opened)//电话已经关闭
		return;
	m_Opened = false;//关闭电话使用标志

	if(hWaveIn){
		waveInStop(hWaveIn);//停止录音
		waveInReset(hWaveIn);//清空录音缓存
		waveInClose(hWaveIn);//关闭录音设备
		hWaveIn = NULL;
	}

	if(m_pChange)
		m_pChange->ShutDown();//停止接收数据

	if(hWaveOut)
	{
		waveOutReset(hWaveOut);//清空声音输出缓存
		waveOutClose(hWaveOut);//关声音输出设备
		hWaveOut = NULL;
	}

	if(m_pChange)
	{
		BYTE Buffer[50];
		while (m_pChange->Receive(Buffer,50) > 0);//清空未接收数据
		delete m_pChange;//删除网络对象
		m_pChange = NULL;
	}
}
