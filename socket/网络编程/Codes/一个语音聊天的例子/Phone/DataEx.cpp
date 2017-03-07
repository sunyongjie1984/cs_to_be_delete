// DataEx.cpp : implementation file
//

#include "stdafx.h"
#include "Phone.h"
#include "DataEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExchange

CExchange::CExchange()
{
	//初始化类私有数据
	DataBlock = 0;
	MaxDataBlock = MAXWAVEBLOCK;
	CurrentBlock = 0;
}

CExchange::~CExchange()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CExchange, CAsyncSocket)
	//{{AFX_MSG_MAP(CExchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CExchange member functions

void CExchange::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char buf[MAXWAVEBUFFER];
	CString Host;
	UINT Port;
	int RecieveLen;

	if(!m_Opened)
		//已经停止播音
		return;

	RecieveLen = this->ReceiveFrom(buf, MAXWAVEBUFFER, Host, Port);
	if(Host != RemoteHost)
	//收到非本次连接数据
		return;

	if(DataBlock < MaxDataBlock)
	{//总播音数据块符合要求
		//char* buff1 = new char[RecieveLen];//申请播音数据内存
		memcpy(WaveHdrOut[CurrentBlock].lpData, buf, RecieveLen);//复制语音数据

		//WaveHdrOut = new WAVEHDR;//申请结构内存
		//为结构赋值
		WaveHdrOut[CurrentBlock].dwBufferLength=RecieveLen;
		WaveHdrOut[CurrentBlock].dwFlags=0;
		WaveHdrOut[CurrentBlock].dwUser=0;
		//准备、锁定内存块
		waveOutPrepareHeader(hWaveOut, &WaveHdrOut[CurrentBlock], sizeof(WAVEHDR));
		//播放该语音数据
		waveOutWrite(hWaveOut, &WaveHdrOut[CurrentBlock], sizeof(WAVEHDR));
		DataBlock++;
		CurrentBlock = (CurrentBlock+1) % MAXWAVEBLOCK;
		MaxDataBlock = MAXWAVEBLOCK;
	}else
	{//总内存块过多，需要减少（到2个）内存块
	 //该设置保证数据最多为 MAXWAVEBLOCK个，最少为2个
	 //在当前设置下，放音最大延时为 0.5秒（忽略网络延时）。
		MaxDataBlock = 3;
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
