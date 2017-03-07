// Regedit.h: interface for the CRegedit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGEDIT_H__15EAD9C6_7207_4E3C_B6A4_04ADB56B09BD__INCLUDED_)
#define AFX_REGEDIT_H__15EAD9C6_7207_4E3C_B6A4_04ADB56B09BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegedit  
{
public:
	CRegedit();
	virtual ~CRegedit();

public:
	static int WriteRegedit( DWORD dwProductType );

	static int ReadRegedit( DWORD &dwProductType );
};

#endif // !defined(AFX_REGEDIT_H__15EAD9C6_7207_4E3C_B6A4_04ADB56B09BD__INCLUDED_)
