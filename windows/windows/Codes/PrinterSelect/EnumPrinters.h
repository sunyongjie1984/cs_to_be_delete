// EnumPrinters.h: interface for the CEnumPrinters class.
//
// Written By : R.I.Allen
// 3rd May 2002
// Roger.Allen@sirius-analytical.com
// You can use this source as you like, but without any warranties of any kind!
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENUMPRINTERS_H__496315A4_5B64_11D6_AD8C_00B0D0652E95__INCLUDED_)
#define AFX_ENUMPRINTERS_H__496315A4_5B64_11D6_AD8C_00B0D0652E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEnumPrinters  
{
public:
					CEnumPrinters();
	virtual			~CEnumPrinters();

	// returning gathered printer information
	int				GetPrinterCount() ;
	CString			GetPrinterName(int index) ;
	CString			GetPrinterLocation(int index) ;
	CString			GetPrinterShareName(int index) ;
	CString			GetPrinterPortName(int index) ;
	// enumerating printers on this and remote machines
	void			ReadLocalPrinters() ;
	// actually changing or configuring the printer
	bool			SetNewPrinter(HANDLE& hDevMode, HANDLE& hDevNames, const CString& PrinterName, const CString& PrinterSpooler, const CString& PrinterPort) ;
	bool			SetNewPrinter(HANDLE& hDevMode, HANDLE& hDevNames, int index) ;
	bool			SetPrintOrientation(HANDLE &hDevMode, int mode) ;
	// saving settings too/from the registry
	bool			SavePrinterSelection(HANDLE &hDevMode, HANDLE& hDevNames) ;
	bool			RestorePrinterSelection(HANDLE &hDevMode, HANDLE& hDevNames) ;
	// debug options only
#ifdef _DEBUG
	void			DumpHandles(HANDLE& hDevMode, HANDLE& hDevNames) ;
#endif
private:
	int				m_NumPrinters ;
	CStringList		m_PrinterName ;
	CStringList		m_PrinterLocation ;
	CStringList		m_PrinterShareName ;
	CStringList		m_PrinterPort ;
};

#endif // !defined(AFX_ENUMPRINTERS_H__496315A4_5B64_11D6_AD8C_00B0D0652E95__INCLUDED_)
