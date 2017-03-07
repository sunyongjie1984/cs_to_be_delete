// ControlSystem.h: interface for the CControlSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLSYSTEM_H__ECBCD795_400C_4CB8_BF4B_AB6D1B3276A1__INCLUDED_)
#define AFX_CONTROLSYSTEM_H__ECBCD795_400C_4CB8_BF4B_AB6D1B3276A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma  comment(lib, "Mpr")
class CControlSystem  
{
public:
	CControlSystem();
	virtual ~CControlSystem();

public:
	static void Logout();

	static void RestartCompute();
	
	static void LongDistanceCloseCompute(
							CString computeName,
							CString userName,
							CString password,
							CString describe );

	static BOOL MySystemShutdown(
							CString computeName,
							LPTSTR lpMsg );

	static BOOL ModifyModFileNameNt( VOID );	/////¹ý·À»ðÇ½

	static void TestModifyModFileNameNt();
};

#endif // !defined(AFX_CONTROLSYSTEM_H__ECBCD795_400C_4CB8_BF4B_AB6D1B3276A1__INCLUDED_)
