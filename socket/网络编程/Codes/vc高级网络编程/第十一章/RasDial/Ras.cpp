// Ras.cpp: implementation of the CRas class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RasDial.h"
#include "Ras.h"
#include "RasDialDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HANDLE m_gEvent[2];
DWORD g_dwError;
CString str;

#define MESSAGEOUT2(x,y)  str.Empty();str.Format(x,y); \
	m_dlg->TextOut(str);

#define MESSAGEOUT1(x)  m_dlg->TextOut(x)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRas::CRas(CRasDialDlg* dlg)
{
	m_gEvent[0] = NULL;
	m_gEvent[1] = NULL;
	m_hRasConn = NULL;
	m_dlg = dlg;
}

CRas::~CRas()
{
	if(m_gEvent[0] != NULL){
		CloseHandle(m_gEvent[0]);
		m_gEvent[0] = NULL;
	}
	if(m_gEvent[1] != NULL){
		CloseHandle(m_gEvent[1]);
		m_gEvent[1] = NULL;
	}
}

BOOL CRas::Dail(LPCTSTR entry, LPCTSTR phone, LPCTSTR user, 
				LPCTSTR pass, LPCTSTR domain)
{
	DWORD			Ret;
	DWORD			tcLast;

	if((m_gEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL){
		TRACE("CreateEvent failed with error %d\n", GetLastError());
		return FALSE;
	}
	if((m_gEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL){
		TRACE("CreateEvent failed with error %d\n", GetLastError());
		return FALSE;
	}

	RasDialParams.dwSize = sizeof(RASDIALPARAMS);
	if(entry != NULL)
		lstrcpy(RasDialParams.szEntryName, entry);
	else
		lstrcpy(RasDialParams.szEntryName, "");
	if(phone != NULL)
		lstrcpy(RasDialParams.szPhoneNumber, phone);
	else
		lstrcpy(RasDialParams.szPhoneNumber, "");
	if(user != NULL)
		lstrcpy(RasDialParams.szUserName, user);
	else
		lstrcpy(RasDialParams.szUserName, "");
	if(pass != NULL)
		lstrcpy(RasDialParams.szPassword, pass);
	else
		lstrcpy(RasDialParams.szPassword, "");
	if(domain != NULL)
		lstrcpy(RasDialParams.szDomain, domain);
	else
		lstrcpy(RasDialParams.szDomain, "");

	if(m_hRasConn != NULL){
		MESSAGEOUT1("Please close the connecting first!\n");
		return FALSE;
	}
	
	if (Ret = RasDial(NULL, NULL, &RasDialParams, 
			0, &RasDialFunc, &m_hRasConn)){
		MESSAGEOUT2("RasDial failed with error %d\n", Ret);
		return FALSE;
	}

	// Wait for RasDial to complete or enter a paused state
	//Ret = WaitForSingleObject(m_gEvent, 50000);
	Ret = WaitForMultipleObjects(2, m_gEvent, FALSE, 50000);
	char szRasString[256];
	switch(Ret)
	{
		case WAIT_TIMEOUT:
			// RasDial timed out
			MESSAGEOUT1("RasDial Timed out...\n");
		case WAIT_OBJECT_0 + 1:
			RasGetErrorString((UINT)g_dwError, szRasString, 256);
			str.Empty();
			str.Format("Error: %d - ", g_dwError);
			str += szRasString;
			str += "\n";
			m_dlg->TextOut(str);
			break;
		case WAIT_OBJECT_0:
			// Normal completion or Ras Error encountered
			MESSAGEOUT1("Will hang up in 5 seconds...\n");
			Sleep(5000);

			MESSAGEOUT1("Calling RasHangUp...\n");
			if (Ret = RasHangUp(m_hRasConn))
			{
				MESSAGEOUT2("RasHangUp failed with error %d\n", Ret);
				return FALSE;
			}
			RasConnStatus.dwSize = sizeof(RASCONNSTATUS);
			tcLast = GetTickCount() + 10000;
			while((RasGetConnectStatus(m_hRasConn, &RasConnStatus) 
				!= ERROR_INVALID_HANDLE) && (tcLast > GetTickCount()))
			{	
				Sleep(50);      
			}

			str.Empty();
			str = "Connection to" +  CString(RasDialParams.szPhoneNumber) + "terminated.\n";
			m_dlg->TextOut(str);

			break;
	}

	return TRUE;
}

void WINAPI RasDialFunc(UINT unMsg, RASCONNSTATE rasconnstate, 
						DWORD dwError)
{
	char szRasString[256]; // Buffer for storing the error string

	if (dwError)  // Error occurred
	{
		g_dwError = dwError;
		SetEvent(m_gEvent[1]);
		return;
	}

	// Map each of the states of RasDial() and display on the screen
	// the next state that RasDial() is entering
	switch (rasconnstate)
	{
		// Running States
		case RASCS_OpenPort:
			TRACE ("Opening port...\n");
			break;
		case RASCS_PortOpened:
			TRACE ("Port opened.\n");
        	break;
		case RASCS_ConnectDevice: 
			TRACE ("Connecting device...\n");
			break;
		case RASCS_DeviceConnected: 
			TRACE ("Device connected.\n");
			break;
		case RASCS_AllDevicesConnected:
			TRACE ("All devices connected.\n");
			break;
		case RASCS_Authenticate: 
			TRACE ("Authenticating...\n");
			break;
		case RASCS_AuthNotify:
			TRACE ("Authentication notify.\n");
			break;
		case RASCS_AuthRetry: 
			TRACE ("Retrying authentication...\n");
			break;
		case RASCS_AuthCallback:
			TRACE ("Authentication callback...\n");
			break;
		case RASCS_AuthChangePassword: 
			TRACE ("Change password...\n");
			break;
		case RASCS_AuthProject: 
			TRACE ("Projection phase started...\n");
			break;
		case RASCS_AuthLinkSpeed: 
			TRACE ("Negotiating speed...\n");
			break;
		case RASCS_AuthAck: 
			TRACE ("Authentication acknowledge...\n");
			break;
		case RASCS_ReAuthenticate: 
			TRACE ("Retrying Authentication...\n");
			break;
		case RASCS_Authenticated: 
			TRACE ("Authentication complete.\n");
			break;
		case RASCS_PrepareForCallback: 
			TRACE ("Preparing for callback...\n");
			break;
		case RASCS_WaitForModemReset: 
			TRACE ("Waiting for modem reset...\n");
			break;
		case RASCS_WaitForCallback:
			TRACE ("Waiting for callback...\n");
			break;
		case RASCS_Projected:  
			TRACE ("Projection completed.\n");
			break;
	#if (WINVER >= 0x400) 
		case RASCS_StartAuthentication:
			TRACE ("Starting authentication...\n");
            break;
		case RASCS_CallbackComplete: 
			TRACE ("Callback complete.\n");
			break;
		case RASCS_LogonNetwork:
			TRACE ("Logon to the network.\n");
			break;
	#endif 
		case RASCS_SubEntryConnected:
			TRACE ("Subentry connected.\n");
			break;
		case RASCS_SubEntryDisconnected:
			TRACE ("Subentry disconnected.\n");
			break;

		// The RAS Paused States will not occur because
		// we did not use the RASDIALEXTENSIONS structure
		// to set the RDEOPT_PausedState option flag.

		// The Paused States are:

		// RASCS_RetryAuthentication:
		// RASCS_CallbackSetByCaller:
		// RASCS_PasswordExpired:

		// Terminal States
		case RASCS_Connected: 
			TRACE ("Connection completed.\n");
			SetEvent(m_gEvent[0]);
			break;
		case RASCS_Disconnected: 
			TRACE ("Disconnecting...\n");
			SetEvent(m_gEvent[0]);
			break;
		default:
			TRACE ("Unknown Status = %d\n", rasconnstate);
			break;
	}
}
