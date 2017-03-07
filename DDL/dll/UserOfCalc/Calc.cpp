#include "Calc.h"
#include <windows.h>

BOOL APIENTRY DllMain (HANDLE, DWORD, LPVOID)					 
{
    return TRUE;
}

// Ctor, initializes the m_szLastFuncCalled array
CCalc::CCalc ()
{
	
	memset (m_szLastUsedFunc, 0, sizeof (m_szLastUsedFunc));
	strcpy (m_szLastUsedFunc, "No function used yet");	
}


int CCalc::Add (int i, int j)
{
	strcpy (m_szLastUsedFunc, "Add used");	
	return (i + j);	
}

int CCalc::Sub (int i, int j)
{
	strcpy (m_szLastUsedFunc, "Sub used");
	return (i - j);	
}

// returns the last function that was called. ie. it returns 
// either "No function used yet" or "Add used" or "Sub used"
TCHAR* CCalc::GetLastUsedFunc ()
{
	return m_szLastUsedFunc;
}

