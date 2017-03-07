#include "windows.h"
#include "stdio.h"
#include "main.h"

#define READ_BUF_SIZE 256
#define READ_TIMEOUT      5000      // milliseconds
#define EVENTFLAG_DEFAULT	EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD

void main(int argc, char *argv[] )
{
	HANDLE	hComm;
	DWORD	dwRead;
	BOOL	fWaitingOnRead = FALSE;
	OVERLAPPED osReader = {0};
	BYTE	lpBuf[ READ_BUF_SIZE ];
	DWORD dwRes;
	COMMTIMEOUTS CommTimeouts = { 0 };
	DCB   dcb = { 0 };
	OVERLAPPED osStatus = { 0 };
	DWORD dwCommEvent;
	
	hComm = CreateFile( "COM5",
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		0, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		0);
	if( hComm == INVALID_HANDLE_VALUE ){
		printf("CreateFile failed with code 0x%x\n", GetLastError() );
		goto FAILED;
	}
	if( !GetCommTimeouts( hComm, &CommTimeouts ) ){
		printf("GetCommTimeouts failed with code 0x%x\n", GetLastError() );
		goto FAILED;
	}
	dcb.DCBlength = sizeof( DCB );
	if( !GetCommState( hComm, &dcb ) ){
		printf("GetCommState failed with code 0x%x\n", GetLastError() );
		goto FAILED;
	}
	osStatus.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if( osStatus.hEvent == NULL ){
		printf("CreateEvent(Status Event) failed\n");
		goto FAILED;
	}
	dwRes = SetCommMask( hComm, EVENTFLAG_DEFAULT );
	dwRes = 0;
	dwRes = WaitCommEvent( hComm, &dwCommEvent, &osStatus );
	if( dwRes ){
		printf("WaitCommEvent OK\n");
	}else{
		dwRes = WaitForSingleObject( osStatus.hEvent, 3000 );
		switch( dwRes ){
		case WAIT_OBJECT_0:
			printf("Event is set\n");
			break;
		case WAIT_TIMEOUT:
			printf("Timeout\n");
			break;
		}
	}

	CloseHandle( osStatus.hEvent );
FAILED:
	CloseHandle( hComm );
}
void HandleASuccessfulRead( LPBYTE lpBuf, int dwRead )
{
	printf("In HandleASuccessfulRead routine\n");
}

#if 0
	// Create the overlapped event. Must be closed before exiting
	// to avoid a handle leak.
	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	if (osReader.hEvent == NULL){
		printf("osReader.hEvent failed\n");
		goto FAILED;
	}
	if (!fWaitingOnRead) {
		// Issue read operation.
		if (!ReadFile(hComm, lpBuf, READ_BUF_SIZE, &dwRead, &osReader)) {
			if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
				printf("ReaderFile return immediately\n");
			// Error in communications; report it.
			else
				fWaitingOnRead = TRUE;
		}
		else {    
			// read completed immediately
			HandleASuccessfulRead(lpBuf, dwRead);
		}
	}
	if (fWaitingOnRead) {
		dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
		switch(dwRes)
		{
			// Read completed.
		case WAIT_OBJECT_0:
			if (!GetOverlappedResult(hComm, &osReader, &dwRead, FALSE)){
				// Error in communications; report it.
				printf("Read completed but no data\n");
			}
			else{
				// Read completed successfully.
				HandleASuccessfulRead(lpBuf, dwRead);
			}
			//  Reset flag so that another opertion can be issued.
			fWaitingOnRead = FALSE;
			break;
			
		case WAIT_TIMEOUT:
			// Operation isn't complete yet. fWaitingOnRead flag isn't
			// changed since I'll loop back around, and I don't want
			// to issue another read until the first one finishes.
			//
			// This is a good time to do some background work.
			printf("Time out\n");
			break;                       
			
		default:
			// Error in the WaitForSingleObject; abort.
			// This indicates a problem with the OVERLAPPED structure's
			// event handle.
			break;
		}
	}
	CloseHandle( osReader.hEvent );
#endif