// FileBase.h: interface for the CFileBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEBASE_H__24064229_A828_4B17_B374_8FAC1C4AAD5A__INCLUDED_)
#define AFX_FILEBASE_H__24064229_A828_4B17_B374_8FAC1C4AAD5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <share.h>
#include <string>

#define __SUCCESS	0
#define __FAILED	-1

#define __LEN_260	260
#define __LEN_1024	1024
#define	__MILLION	10/*__LEN_1024 * __LEN_1024*/

#define __FILE_OPEN	 TRUE
#define __FILE_CLOSE FALSE

class CFileBase  
{
public:
	CFileBase();
	virtual ~CFileBase();

public:


};

#endif // !defined(AFX_FILEBASE_H__24064229_A828_4B17_B374_8FAC1C4AAD5A__INCLUDED_)
