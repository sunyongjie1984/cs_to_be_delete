// ControlRegedit.h: interface for the CControlRegedit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLREGEDIT_H__45F88951_CAFE_467D_B329_3B80E122C406__INCLUDED_)
#define AFX_CONTROLREGEDIT_H__45F88951_CAFE_467D_B329_3B80E122C406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CControlRegedit  
{
public:
	CControlRegedit();
	virtual ~CControlRegedit();

public:
	static int CreateSpecifyRegeditKey(
							IN		HKEY		hkRootName,
							IN		LPTSTR		RegKeyPath,
							IN		LPTSTR		lpSpecifyKeyName,
							IN      DWORD		dwSpecifyData	);

	static int ReadSpecifyRegeditKeyValue(
							IN			  HKEY     hkRootName,
							IN			  LPTSTR   RegKeyPath,
							IN		      LPTSTR   lpRegSpecifyKeyName,
							IN		OUT   DWORD	  &dwKeyValue );

};

#endif // !defined(AFX_CONTROLREGEDIT_H__45F88951_CAFE_467D_B329_3B80E122C406__INCLUDED_)
