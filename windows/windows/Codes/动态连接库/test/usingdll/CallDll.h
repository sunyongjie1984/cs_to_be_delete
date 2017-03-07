// CallDll.h: interface for the CCallDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLDLL_H__CA0FC6A7_CAB7_4301_B0EC_46ABD337B06B__INCLUDED_)
#define AFX_CALLDLL_H__CA0FC6A7_CAB7_4301_B0EC_46ABD337B06B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef BOOL  ( * _MyMsgBox )();
typedef BOOL  ( * _aMsgBoxA )( HWND   hwnd,
							   LPCSTR lpText,
							   LPCSTR lpCaption );

class CCallDll  
{
public:
	CCallDll();
	virtual ~CCallDll();

	_MyMsgBox MyMsgBox;
	_aMsgBoxA  aMsgBoxA;
private:
	HMODULE m_hmyDll;
};

#endif // !defined(AFX_CALLDLL_H__CA0FC6A7_CAB7_4301_B0EC_46ABD337B06B__INCLUDED_)
