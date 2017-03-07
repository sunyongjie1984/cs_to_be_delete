// COMMHOOK.cpp - main module for VxD COMMHOOK

#define DEVICE_MAIN
#include "commhook.h"
Declare_Virtual_Device(COMMHOOK)
#undef DEVICE_MAIN

CommhookVM::CommhookVM(VMHANDLE hVM) : VVirtualMachine(hVM) {}

CommhookThread::CommhookThread(THREADHANDLE hThread) : VThread(hThread) {}


// 
// These are used to store the original service addresses
// and the thunks that are used by the hook and unhook
// functions
COMMPORTHANDLE	(*VCOMM_OpenCommService)(PCHAR,VMHANDLE);
HDSC_Thunk		thunkVCOMM_OpenCommHook;
BOOL			(*VCOMM_CloseCommService)(COMMPORTHANDLE);
HDSC_Thunk		thunkVCOMM_CloseCommHook;
BOOL			(*VCOMM_ReadCommService)(COMMPORTHANDLE,PVOID,DWORD,PDWORD);
HDSC_Thunk		thunkVCOMM_ReadCommHook;
BOOL			(*VCOMM_WriteCommService)(COMMPORTHANDLE,PVOID,DWORD,PDWORD);
HDSC_Thunk		thunkVCOMM_WriteCommHook;


// A pointer to the device context. This is a hack to let
// these non-members of the device class get to its data.
CommhookDevice	*CHD;

struct
	{
	char			name[100];
	COMMPORTHANDLE	handle;
	} OpenPorts[10];

// My hook for the VCOMM_OpenComm service. I call the
// original handler, check the return value, then see
// if the opened port was the one I was watching for.
COMMPORTHANDLE VCOMM_OpenCommHook( PCHAR szPortName, VMHANDLE VMid )
	{
	COMMPORTHANDLE retval = VCOMM_OpenCommService( szPortName, VMid );

	if ( (retval != IE_BADID && retval != IE_OPEN) &&
		 CHD->cpTargetPortName != NULL &&
		 !stricmp( szPortName, CHD->cpTargetPortName ) )
		{
		CHD->hPort = retval;
		CHD->sAccessStats.dwOpenCount++;
		}

	return retval;
	}

// My hook for the VCOMM_CloseComm service. I check the port
// handle passed in to see if it was the one I was watching
// (or if I hadn't seen an open yet) then call the original
// service.
BOOL VCOMM_CloseCommHook( COMMPORTHANDLE hPort )
	{
	if ( CHD->hPort == hPort && CHD->hPort != NULL )
		{
		CHD->sAccessStats.dwCloseCount++;
		CHD->hPort = NULL;
		}
	else if ( CHD->hPort == NULL )
		{
		CHD->sAccessStats.dwNotMineCloseCount++;
		}

	return VCOMM_CloseCommService( hPort );
	}

// My hook for the VCOMM_ReadComm service. I call the original
// service, then check the port handle. If it was the one I
// was watching (or if I hadn't seen an open yet), I add the
// read data to a list of "trace blocks".
BOOL VCOMM_ReadCommHook( COMMPORTHANDLE hPort, PVOID buf, DWORD nRequest, PDWORD pNRead )
	{
	BOOL retval = VCOMM_ReadCommService( hPort, buf, nRequest, pNRead );

	if ( CHD->hPort == hPort || CHD->hPort == NULL )
		{
		CHD->sAccessStats.dwReadCount++;
		CHD->sAccessStats.dwReadBytes += *pNRead;

		CHD->AddTraceBlock( (unsigned char *)buf, false, *pNRead );
		}

	return retval;
	}

// My hook for the VCOMM_WriteComm service. I call the original
// service, then check the port handle. If it was the one I
// was watching (or if I hadn't seen an open yet), I add the
// written data to a list of "trace blocks".
// NOTE THE USE OF THE MUTEX. SINCE I WANT TO BE ABLE TO WRITE
// TO THE PORT (INJECTING MY OWN DATA), I SYNCHRONIZE ACCESS
// TO THE VCOMM_WriteComm SERVICE. I DON'T REALLY KNOW IF THIS
// IS NECESSARY.
BOOL VCOMM_WriteCommHook( COMMPORTHANDLE hPort, PVOID buf, DWORD nRequest, PDWORD pNWritten )
	{
	if ( CHD->hPort == hPort || CHD->hPort == NULL )
		{
		CHD->mutexWrite->enter();
		}

	BOOL rv = VCOMM_WriteCommService( hPort, buf, nRequest, pNWritten );

	if ( CHD->hPort == hPort || CHD->hPort == NULL )
		{
		CHD->mutexWrite->leave();
		CHD->sAccessStats.dwWriteCount++;
		CHD->sAccessStats.dwWriteBytes += *pNWritten;

		CHD->AddTraceBlock( (unsigned char *)buf, true, *pNWritten );
		}

	return rv;
	}

// Remove the head of the trace block list and return it, adjusting
// the total trace size.
CDataBlock *CommhookDevice::GetNextTraceBlock()
	{
	mutexTrace->enter();

	CDataBlock *pNext = m_pFirstTraceBlock;
	if ( m_pFirstTraceBlock != NULL )
		m_pFirstTraceBlock = m_pFirstTraceBlock->m_pNextBlock;
	if ( m_pFirstTraceBlock == NULL )
		m_pLastTraceBlock = NULL;

	if ( pNext != NULL )
		m_dwTraceSize -= pNext->m_dwLength;

	mutexTrace->leave();

	return pNext;
	}

// Add a block to the tail of the trace block list, adjusting the size.
void CommhookDevice::AddTraceBlock( unsigned char *pData, bool bWritten, DWORD dwLength )
	{
	if ( dwLength )
		{
		mutexTrace->enter();

		CDataBlock *pNewBlock = new CDataBlock( pData, bWritten, dwLength );
		if ( m_pFirstTraceBlock == NULL )
			m_pFirstTraceBlock = pNewBlock;
		else
			m_pLastTraceBlock->m_pNextBlock = pNewBlock;

		m_pLastTraceBlock = pNewBlock;

		m_dwTraceSize += pNewBlock->m_dwLength;

		mutexTrace->leave();
		}
	}

// Install the hooks. Note that the VCOMM services I'm hooking
// follow the C calling convention, so I use Hook_Device_Service_C
VOID CommhookDevice::DoHooks( void )
{
	// hook the open comm service
	VCOMM_OpenCommService = (COMMPORTHANDLE(*)(PCHAR,VMHANDLE))
			Hook_Device_Service_C(	___VCOMM_OpenComm,
									VCOMM_OpenCommHook,
									&thunkVCOMM_OpenCommHook);

	// hook the close comm service
	VCOMM_CloseCommService = (BOOL(*)(COMMPORTHANDLE))
			Hook_Device_Service_C(	___VCOMM_CloseComm,
									VCOMM_CloseCommHook,
									&thunkVCOMM_CloseCommHook);

	// hook the read comm service
	VCOMM_ReadCommService = (BOOL(*)(COMMPORTHANDLE,PVOID,DWORD,PDWORD))
			Hook_Device_Service_C(	___VCOMM_ReadComm,
									VCOMM_ReadCommHook,
									&thunkVCOMM_ReadCommHook);

	// hook the write comm service
	VCOMM_WriteCommService = (BOOL(*)(COMMPORTHANDLE,PVOID,DWORD,PDWORD))
			Hook_Device_Service_C(	___VCOMM_WriteComm,
									VCOMM_WriteCommHook,
									&thunkVCOMM_WriteCommHook);
}

// Uninstall the hooks with Unhook_Device_Service_C
VOID CommhookDevice::DoUnhooks( void )
{
	// unhook the open comm service
	Unhook_Device_Service_C(___VCOMM_OpenComm,
							&thunkVCOMM_OpenCommHook);

	// unhook the close comm service
	Unhook_Device_Service_C(___VCOMM_CloseComm,
							&thunkVCOMM_CloseCommHook);

	// unhook the read comm service
	Unhook_Device_Service_C(___VCOMM_ReadComm,
							&thunkVCOMM_ReadCommHook);

	// unhook the write comm service
	Unhook_Device_Service_C(___VCOMM_WriteComm,
							&thunkVCOMM_WriteCommHook);

}


void CommhookDevice::ClearStats( void )
	{
	sAccessStats.dwOpenCount =
		sAccessStats.dwCloseCount = 
		sAccessStats.dwNotMineCloseCount = 
		sAccessStats.dwReadCount = 
		sAccessStats.dwReadBytes =
		sAccessStats.dwWriteCount =
		sAccessStats.dwWriteBytes = 0;
	}

void CommhookDevice::SetupData( void )
	{
	ClearStats();

	pHandles = NULL;
	nNumHandles = 0;

	CHD = this;

	mutexWrite = new VMutex;
	mutexTrace = new VMutex;

	cpTargetPortName = NULL;
	hPort = NULL;

	for ( int i=0; i<10; i++ )
		{
		memset( OpenPorts[i].name, 0, 100 );
		OpenPorts[i].handle = NULL;
		}

	FilteredRead = 
		FilteredWrite =
		FilteredCount = 0;

	m_pFirstTraceBlock = 
		m_pLastTraceBlock = NULL;
	m_dwTraceSize = 0;
	}


void CommhookDevice::DeleteHandles( void )
	{
	if ( pHandles != NULL )
		{
		int i;
		for ( i=0; i<nNumHandles; i++ )
			VWIN32_CloseVxDHandle( pHandles[i] );
		delete[] pHandles;
		pHandles = NULL;
		}
	}

void CommhookDevice::Cleanup( void )
	{
	DeleteHandles();
	delete mutexWrite;
	delete[] cpTargetPortName;

	mutexTrace->enter();
	CDataBlock *pBlock;
	while ( (pBlock = GetNextTraceBlock()) != NULL )
		delete pBlock;
	mutexTrace->leave();
	delete mutexTrace;
	}


BOOL CommhookDevice::OnSysCriticalInit(VMHANDLE hSysVM, PCHAR pszCmdTail, PVOID refData)
{
	SetupData();
	DoHooks();
	return TRUE;
}

VOID CommhookDevice::OnSysCriticalExit()
{
	DoUnhooks();
	Cleanup();
}

BOOL CommhookDevice::OnSysDynamicDeviceInit()
{
	SetupData();
	DoHooks();
	return TRUE;
}

BOOL CommhookDevice::OnSysDynamicDeviceExit()
{
	DoUnhooks();
	Cleanup();
	return TRUE;
}

// My client app uses DeviceIoControl() to communicate with
// this VxD.
DWORD CommhookDevice::OnW32DeviceIoControl(PIOCTLPARAMS pDIOCParams)
{

    switch ( pDIOCParams->dioc_IOCtlCode )
		{
		default:
			*pDIOCParams->dioc_bytesret = -1;
			break;

		case 0:	//DIOC_OPEN:
		case -1: //DIOC_CLOSE:
			*pDIOCParams->dioc_bytesret = -2;
			break;

		// Get statistics on the number of opens, closes, etc.
		// pDIOCParams->dioc_OutBuf must point to an _sAccessStats structure.
		case _CommHook_DIOC_AccessStats:
			memcpy( pDIOCParams->dioc_OutBuf, &sAccessStats, sizeof(sAccessStats ) );
			*pDIOCParams->dioc_bytesret = sizeof(sAccessStats);
			break;

		// Clear the statistics.
		case _CommHook_DIOC_ClearStats:
			ClearStats();
			*pDIOCParams->dioc_bytesret = 0;
			break;

		// Pass in handles to events that the VxD can use to signal
		// the app. The app must have used OpenVxDHandle() from Kernel32
		// to create the Ring0 handle.
		// pDIOCParams->dioc_cbInBuf is the count of handles
		// pDIOCParams->dioc_InBuf is an array of handles
		case _CommHook_DIOC_Handles:
			{
			DeleteHandles();

			nNumHandles = (int)pDIOCParams->dioc_cbInBuf;
			pHandles = new HANDLE[ nNumHandles ];

			for ( int i=0; i<nNumHandles; i++ )
				pHandles[i] = ((HANDLE *)pDIOCParams->dioc_InBuf)[i];
			
			*pDIOCParams->dioc_bytesret = 0;
			}
			break;

		// Set the port name that we want to watch for.
		// pDIOCParams->dioc_cbInBuf is the length of the string not including
		//		the terminating NULL.
		// pDIOCParams->dioc_InBuf points to a NULL-terminated string
		case _CommHook_DIOC_SetTargetPort:
			delete[] cpTargetPortName;

			if ( pDIOCParams->dioc_cbInBuf )
				{
				cpTargetPortName = new char[ pDIOCParams->dioc_cbInBuf + 1 ];
				strcpy( cpTargetPortName, (char *)pDIOCParams->dioc_InBuf );
				}
			else
				cpTargetPortName = NULL;
			*pDIOCParams->dioc_bytesret = 0;
			break;

		// Write a block of data to the open port.
		// pDIOCParams->dioc_cbInBuf is the number of bytes to write
		// pDIOCParams->dioc_InBuf is a pointer to the data.
		// on exit, pDIOCParams->dioc_bytesret contains the number of
		//		bytes actually written.
		case _CommHook_DIOC_WriteToPort:
			*pDIOCParams->dioc_bytesret = 0;
			if ( hPort != NULL )
				{
				int offset = 0;
				DWORD remaining = pDIOCParams->dioc_cbInBuf;
				DWORD written;
				mutexWrite->enter();
				while ( remaining != 0 )
					{
					if ( ! VCOMM_WriteCommService( hPort,
											(char *)pDIOCParams->dioc_InBuf + offset,
											remaining, &written ) )
						break;
					remaining -= written;
					*pDIOCParams->dioc_bytesret += written;
					}
				mutexWrite->leave();
				}
			break;

		// Read filtered data (whose generation is not yet implemented!!!)
		// pDIOCParams->dioc_cbOutBuf is the size of a buffer to fill
		// pDIOCParams->dioc_OutBuf is the app-supplied buffer
		// pDIOCParams->dioc_bytesret will contain the number of bytes
		//    actually read.
		case _CommHook_DIOC_ReadFilteredData:
			*pDIOCParams->dioc_bytesret = 0;
			if ( hPort != NULL &&
				 FilteredCount != 0 )
				{
				for ( int i=0; i<pDIOCParams->dioc_cbOutBuf && FilteredCount; i++ )
					{
					((unsigned char *)pDIOCParams->dioc_OutBuf)[i] = FilteredData[FilteredRead++];
					FilteredRead &= 0x3FF;
					FilteredCount--;
					}
				*pDIOCParams->dioc_bytesret = i;
				}
			break;

		// Read trace (Tx and Rx) data from the trace block list.
		// pDIOCParams->dioc_cbOutBuf is the number of bytes to read,
		//		or zero if the app is asking how much data there is.
		// pDIOCParams->dioc_OutBuf points to the app-supplied buffer. It is
		//		ignored if dioc_cbOutBuf is zero. NOTE THAT THIS BUFFER
		//		MUST ACTUALLY BE TWICE THE SIZE OF THE DATA TO READ, AS WE
		//		GET A WORD FOR EVERY BYTE - THE HIGH BYTE CONTAINS 1 IF THE
		//		LOW BYTE WAS A TRANSMITTED BYTE, OR ZERO IF THE LOW BYTE
		//		WAS A RECEIVED BYTE.
		// On exit, pDIOCParams->dioc_bytesret will contain the number of bytes
		//		actually read, or, if dioc_cbOutBuf was zero, the total number
		//		of bytes of trace data available.
		case _CommHook_DIOC_ReadTraceData:
			{
			DWORD remaining = pDIOCParams->dioc_cbOutBuf;
			if ( ! remaining )		// zero is special - caller wants to know
				{					// how much data there is
				*pDIOCParams->dioc_bytesret = m_dwTraceSize;
				}
			else
				{
				DWORD offset = 0;
				CDataBlock *pBlock;
				while ( (pBlock = GetNextTraceBlock()) != NULL &&
						 pBlock->m_dwLength <= remaining )
					{
					for ( int i=0; i<pBlock->m_dwLength; i++ )
						((unsigned short int *)pDIOCParams->dioc_OutBuf)[offset+i] =
								((pBlock->m_bWritten ? 1 : 0) << 8) |
								 pBlock->m_pData[i];
					offset += pBlock->m_dwLength;
					remaining -= pBlock->m_dwLength;
					delete pBlock;
					}
				*pDIOCParams->dioc_bytesret = offset;
				}
			}
			break;
		}

	return DEVIOCTL_NOERROR;
}

