// EnumPrinters.cpp: implementation of the CEnumPrinters class.
//
// Written By : R.I.Allen
// 3rd May 2002
// Roger.Allen@sirius-analytical.com
// You can use this source as you like, but without any warranties of any kind!
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnumPrinters.h"
#include <Winspool.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEnumPrinters::CEnumPrinters()
{
	// initialise ourselves
	m_NumPrinters = 0 ;
	m_PrinterName.RemoveAll() ;
	m_PrinterLocation.RemoveAll() ;
	m_PrinterShareName.RemoveAll() ;

	ReadLocalPrinters() ;				// get the local printers
}

CEnumPrinters::~CEnumPrinters()
{

}

int CEnumPrinters::GetPrinterCount()
{
	return m_NumPrinters ;
}

CString CEnumPrinters::GetPrinterName(int index)
{
	ASSERT(index >= 0 && index < m_NumPrinters) ;
	POSITION	pos ;

	pos = m_PrinterName.GetHeadPosition() ;
	while (pos && index > 0)
		{
		// traverse the list
		m_PrinterName.GetNext(pos) ;
		index-- ;
		}
	if (pos)
		return m_PrinterName.GetAt(pos) ;
	return CString("Error") ;
}

CString CEnumPrinters::GetPrinterLocation(int index)
{
	ASSERT(index >= 0 && index < m_NumPrinters) ;
	POSITION	pos ;

	pos = m_PrinterLocation.GetHeadPosition() ;
	while (pos && index > 0)
		{
		// traverse the list
		m_PrinterLocation.GetNext(pos) ;
		index-- ;
		}
	if (pos)
		return m_PrinterLocation.GetAt(pos) ;
	return CString("Error") ;
}

CString CEnumPrinters::GetPrinterShareName(int index)
{
	ASSERT(index >= 0 && index < m_NumPrinters) ;
	POSITION	pos ;

	pos = m_PrinterShareName.GetHeadPosition() ;
	while (pos && index > 0)
		{
		// traverse the list
		m_PrinterShareName.GetNext(pos) ;
		index-- ;
		}
	if (pos)
		return m_PrinterShareName.GetAt(pos) ;
	return CString("Error") ;
}

CString CEnumPrinters::GetPrinterPortName(int index)
{
	ASSERT(index >= 0 && index < m_NumPrinters) ;
	POSITION	pos ;

	pos = m_PrinterPort.GetHeadPosition() ;
	while (pos && index > 0)
		{
		// traverse the list
		m_PrinterPort.GetNext(pos) ;
		index-- ;
		}
	if (pos)
		return m_PrinterPort.GetAt(pos) ;
	return CString("Error") ;
}


void CEnumPrinters::ReadLocalPrinters()
{
	DWORD		Flags = PRINTER_ENUM_FAVORITE | PRINTER_ENUM_LOCAL; //local printers
	DWORD		cbBuf;
	DWORD		pcReturned ;
	DWORD		index;
	DWORD		Level = 2;
	TCHAR		Name[500] ;
	LPPRINTER_INFO_2 pPrinterEnum = NULL ;

	memset(Name, 0, sizeof(TCHAR) * 500) ;
	::EnumPrinters(Flags, Name, Level, NULL, 0, &cbBuf, &pcReturned) ;
	pPrinterEnum = (LPPRINTER_INFO_2)LocalAlloc(LPTR, cbBuf + 4) ;

	if (!pPrinterEnum)
		{
		TRACE("Error %1d\n", GetLastError()) ;
		goto clean_up;
		}

	if (!EnumPrinters(
			Flags,							// DWORD Flags, printer object types 
			Name,							// LPTSTR Name, name of printer object 
			Level,							// DWORD Level, information level 
			(LPBYTE)pPrinterEnum,			// LPBYTE pPrinterEnum, printer information buffer 
			cbBuf,							// DWORD cbBuf, size of printer information buffer
			&cbBuf,							// LPDWORD pcbNeeded, bytes received or required 
			&pcReturned)					// LPDWORD pcReturned number of printers enumerated 
			)
			{
			TRACE("Error %1d\n", GetLastError()) ;
			goto clean_up;
			}

	if (pcReturned > 0)
		{
		TRACE("Found %1d printers\n", pcReturned) ;
		for (index = 0; index < pcReturned; index++)
			{
			m_PrinterName.AddTail((pPrinterEnum + index)->pPrinterName) ;
			m_PrinterShareName.AddTail((pPrinterEnum + index)->pShareName) ;
			m_PrinterLocation.AddTail((pPrinterEnum + index)->pLocation) ;
			m_PrinterPort.AddTail((pPrinterEnum + index)->pPortName) ;
			m_NumPrinters++ ;
			TRACE("Printer          : %1d\n", index + 1) ;
			TRACE("Share name       : %s\n", (pPrinterEnum + index)->pShareName) ;
			TRACE("Printer name     : %s\n", (pPrinterEnum + index)->pPrinterName) ;
			TRACE("Printer location : %s\n", (pPrinterEnum + index)->pLocation) ;
			TRACE("Printer port     : %s\n", (pPrinterEnum + index)->pPortName) ;
			}
		}
clean_up:
	LocalFree(LocalHandle(pPrinterEnum)) ;
}

bool CEnumPrinters::SetNewPrinter(HANDLE& hDevMode, HANDLE& hDevNames, const CString& PrinterName, const CString& PrinterSpooler, const CString& PrinterPort)
// hDeMode - Handle to the current DEVMODE structure
// hDevNames - Handle to the current DEVNAMES structure
// PrinterName - E.g. HP LaserJet 4L
// PrinterSpooler - e.g. "winspool"
// PrinterPort - e.g. "LPT1:"
{
	// we only update the existing hDevMode and hDevNames objects if we can successfgully setup the
	// new hDevMode and hDevNames objects
	HANDLE	local_hDevMode = INVALID_HANDLE_VALUE ;
	HANDLE	local_hDevNames = INVALID_HANDLE_VALUE ;
#ifdef _DEBUG
	DumpHandles(hDevMode, hDevNames) ;
#endif

	// To setup the new local_hDevMode object we need to open the printer name to get the information
	HANDLE	hPrinter;
	char	*pPrinter = new char[PrinterName.GetLength() + 1] ;
	ASSERT(pPrinter) ;
	strcpy(pPrinter, PrinterName) ;
	if (!OpenPrinter(pPrinter, &hPrinter, NULL))
		{
		delete []pPrinter ;
		return false ;
		}

	// A zero for last param returns the size of buffer needed for the information to be returned
	int nSize = DocumentProperties(NULL, hPrinter, pPrinter, NULL, NULL, 0);
	ASSERT(nSize >= 0);
	local_hDevMode = ::GlobalAlloc(GHND, nSize) ;							// allocate on heap
	LPDEVMODE lpDevMode = (LPDEVMODE)::GlobalLock(local_hDevMode);		// lock it

	// Fill in the rest of the structure.
	if (DocumentProperties(NULL, hPrinter, pPrinter, lpDevMode, NULL, DM_OUT_BUFFER) != IDOK)
		{
		// failed to read printer properties, abort
		ASSERT(::GlobalFlags(local_hDevMode) != GMEM_INVALID_HANDLE);
		UINT nCount = ::GlobalFlags(local_hDevMode) & GMEM_LOCKCOUNT;
		while (nCount--)
			::GlobalUnlock(local_hDevMode);

		// finally, really free the handle
		::GlobalFree(local_hDevMode);
		local_hDevMode = NULL;
		ClosePrinter(hPrinter);
		delete []pPrinter ;
		return false ;
		}
	// finsihed interrogating for DEVMODE structure
	::GlobalUnlock(local_hDevMode) ;
	ClosePrinter(hPrinter);
	delete []pPrinter ;

	// we need to allocate a new DEVNAMES object on the global heap
	// we also need the size to include the strings PrinterName, PrinterSpooler and PrinterPort
	// Layout is:
	// DEVNAMES structure
	// PrinterSpooler\0
	// PrinterName\0
	// PrinterPort\0
	int	size = sizeof(DEVNAMES) + PrinterName.GetLength() + 1 + PrinterSpooler.GetLength() + 1 + PrinterPort.GetLength() + 1 ;
	local_hDevNames = ::GlobalAlloc(GHND, size) ;								// allocate on heap
	LPDEVNAMES	pNewDevNames = (LPDEVNAMES)::GlobalLock(local_hDevNames) ;	// lock it
	memset(pNewDevNames, 0, size) ;											// init to 0
	
	// add the 3 strings to the end of the structure
	strcpy((char*)((char*)pNewDevNames + sizeof(DEVNAMES)), PrinterSpooler) ;
	pNewDevNames->wDriverOffset = sizeof(DEVNAMES) ;
	strcpy((char*)((char*)pNewDevNames + sizeof(DEVNAMES)) + PrinterSpooler.GetLength() + 1, PrinterName) ;
	pNewDevNames->wDeviceOffset = sizeof(DEVNAMES) + PrinterSpooler.GetLength() + 1 ;
	strcpy((char*)((char*)pNewDevNames + sizeof(DEVNAMES)) + PrinterSpooler.GetLength() + 1 + PrinterName.GetLength() + 1, PrinterPort) ;
	pNewDevNames->wOutputOffset = sizeof(DEVNAMES) + PrinterSpooler.GetLength() + 1 + PrinterName.GetLength() + 1 ;
	//pNewDevNames->wDefault = lpDevNames->wDefault ;
	::GlobalUnlock(local_hDevNames) ;											// free it
#ifdef _DEBUG
	DumpHandles(local_hDevMode, local_hDevNames) ;
#endif
	// now update the handles that were passed in
	// free the existing handles if they exist first
	if (hDevMode != NULL && hDevMode != INVALID_HANDLE_VALUE)
		{
		ASSERT(::GlobalFlags(hDevMode) != GMEM_INVALID_HANDLE);
		UINT nCount = ::GlobalFlags(hDevMode) & GMEM_LOCKCOUNT;
		while (nCount--)
			::GlobalUnlock(hDevMode);

		// finally, really free the handle
		::GlobalFree(hDevMode);
		hDevMode = INVALID_HANDLE_VALUE ;
		}
	if (hDevNames != NULL && hDevNames != INVALID_HANDLE_VALUE)
		{
		ASSERT(::GlobalFlags(hDevNames) != GMEM_INVALID_HANDLE);
		UINT nCount = ::GlobalFlags(hDevNames) & GMEM_LOCKCOUNT;
		while (nCount--)
			::GlobalUnlock(hDevNames);

		// finally, really free the handle
		::GlobalFree(hDevNames);
		hDevNames = INVALID_HANDLE_VALUE ;
		}
	hDevMode = local_hDevMode ;
	hDevNames = local_hDevNames ;

#ifdef _DEBUG
	DumpHandles(hDevMode, hDevNames) ;
#endif
	return true ;			// success!
}


bool CEnumPrinters::SetNewPrinter(HANDLE& hDevMode, HANDLE& hDevNames, int index)
{
	CString	printer = GetPrinterName(index) ;
	CString spooler("winspool") ;
	CString	port = GetPrinterPortName(index) ;

	return SetNewPrinter(hDevMode, hDevNames, printer, spooler, port) ;
}

bool CEnumPrinters::SavePrinterSelection(HANDLE &hDevMode, HANDLE& hDevNames)
{
	CWinApp* pApp = AfxGetApp() ;
	ASSERT(pApp) ;

	// save the current printer name, spooler and port to the registry
	CString	printer ;
	CString	spooler ;
	CString	port ;
	int		landscape = DMORIENT_PORTRAIT ;

	if (hDevNames != INVALID_HANDLE_VALUE)
		{
		LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(hDevNames);
		
		printer = (char*)((char*)lpDevNames + lpDevNames->wDeviceOffset) ;
		spooler = (char*)((char*)lpDevNames + lpDevNames->wDriverOffset) ;
		port = (char*)((char*)lpDevNames + lpDevNames->wOutputOffset) ;
		::GlobalUnlock(hDevNames) ;
		}
	else
		return false ;				// not setup!

	// get the landscape/portrait mode of the printer
	if (hDevMode != INVALID_HANDLE_VALUE)
		{
		LPDEVMODE lpDevMode = (LPDEVMODE)::GlobalLock(hDevMode) ;
		// get orientation
		landscape = lpDevMode->dmOrientation ;
		::GlobalUnlock(hDevMode) ;
		}
	
	VERIFY(pApp->WriteProfileString("PrinterConfig", "PrinterName", printer)) ;
	VERIFY(pApp->WriteProfileString("PrinterConfig", "Spooler", spooler)) ;
	VERIFY(pApp->WriteProfileString("PrinterConfig", "Port", port)) ;
	VERIFY(pApp->WriteProfileInt("PrinterConfig", "Landscape", landscape)) ;
	return true ;
}

bool CEnumPrinters::RestorePrinterSelection(HANDLE &hDevMode, HANDLE& hDevNames)
{
	// read the settings back from the registry
	// abort if not present
	CString	printer ;
	CString	spooler ;
	CString	port ;
	int		landscape = DMORIENT_PORTRAIT ;
	CWinApp* pApp = AfxGetApp() ;
	ASSERT(pApp) ;

	printer = pApp->GetProfileString("PrinterConfig", "PrinterName", "") ;
	spooler = pApp->GetProfileString("PrinterConfig", "Spooler", "") ;
	port = pApp->GetProfileString("PrinterConfig", "Port", "") ;
	landscape = pApp->GetProfileInt("PrinterConfig", "Landscape", DMORIENT_PORTRAIT) ;

	if (printer == "" || spooler == "" || port == "")
		return false ;								// not setup

	// make sure the selected printer is in the list available
	for (int i = 0 ; i < m_NumPrinters ; i++)
		{
		if (printer == GetPrinterName(i))
			break ;				// found!
		}
	if (i >= m_NumPrinters)
		{
		// the selected printer is no longer available
		AfxMessageBox("Warning : Unable to re-select your preffered printer\n"
						"as it is no longer available. The system default printer\n"
						"will be used.") ;
		return false ;
		}
	VERIFY(SetNewPrinter(hDevMode, hDevNames, printer, spooler, port)) ;
	VERIFY(SetPrintOrientation(hDevMode, landscape)) ;
	return true ;
}


bool CEnumPrinters::SetPrintOrientation(HANDLE &hDevMode, int mode)
{
	if (hDevMode == INVALID_HANDLE_VALUE)
		return false ;

	switch (mode)
		{
		case DMORIENT_PORTRAIT :
				{
				// portrait mode
				LPDEVMODE pDevMode = (LPDEVMODE)::GlobalLock(hDevMode) ;
				// set orientation to portrait
				pDevMode->dmOrientation = DMORIENT_PORTRAIT ;
				::GlobalUnlock(hDevMode) ;
				}
				break ;
		case DMORIENT_LANDSCAPE :
				{
				// landscape mode
				LPDEVMODE pDevMode = (LPDEVMODE)::GlobalLock(hDevMode) ;
				// set orientation to landscape
				pDevMode->dmOrientation = DMORIENT_LANDSCAPE ;
				::GlobalUnlock(hDevMode) ;
				}
				break ;
		default :	
				ASSERT(FALSE) ;		// invalid parameter
				return false ;
		}
	return true ;
}

#ifdef _DEBUG

void CEnumPrinters::DumpHandles(HANDLE& hDevMode, HANDLE& hDevNames)
{
	// dump the content of the handles to the debug output
	TRACE("===================Dumping Print Object handles==============\n") ;
	if (hDevMode != INVALID_HANDLE_VALUE && hDevMode != NULL)
		{
		LPDEVMODE lpDevMode = (LPDEVMODE)::GlobalLock(hDevMode);		// lock it
		TRACE("------hDevMode---------------------------\n") ;
		TRACE("Device name          : %s\n", lpDevMode->dmDeviceName) ;
		TRACE("dmSpecVersion        : %d\n", lpDevMode->dmSpecVersion) ;
		TRACE("dmDriverVersion      : %d\n", lpDevMode->dmDriverVersion) ;
		TRACE("dmSize               : %d\n", lpDevMode->dmSize) ;
		TRACE("dmDriverExtra        : %d\n", lpDevMode->dmDriverExtra) ;
		TRACE("dmFIelds             : %x\n", lpDevMode->dmFields) ;
		TRACE("dmScale              : %d\n", lpDevMode->dmScale) ;
		TRACE("dmCopies             : %d\n", lpDevMode->dmCopies) ;
		TRACE("dmDefaultSource      : %d\n", lpDevMode->dmDefaultSource) ;
		TRACE("dmPrintQuality       : %d\n", lpDevMode->dmPrintQuality) ;
		TRACE("dmColor              : %d\n", lpDevMode->dmColor) ;
		TRACE("dmDuplex             : %d\n", lpDevMode->dmDuplex) ;
		TRACE("dmYResolution        : %d\n", lpDevMode->dmYResolution) ;
		TRACE("dmTTOption           : %d\n", lpDevMode->dmTTOption) ;
		TRACE("dmCollate            : %d\n", lpDevMode->dmCollate) ;
		TRACE("dmFormName           : %s\n", lpDevMode->dmFormName) ;
		TRACE("dmLogPixels          : %d\n", lpDevMode->dmLogPixels) ;
		TRACE("dmBitsPerPel         : %d\n", lpDevMode->dmBitsPerPel) ;
		TRACE("dmPelsWidth          : %d\n", lpDevMode->dmPelsWidth) ;
		TRACE("dmPelsHeight         : %d\n", lpDevMode->dmPelsHeight) ;
		TRACE("dmNup/dmDisplayFlags : %d\n", lpDevMode->dmDisplayFlags) ;
		TRACE("dmDisplayFrequency   : %d\n", lpDevMode->dmDisplayFrequency) ;
		::GlobalUnlock(hDevMode) ;
		}
	else
		TRACE("hDevMode             : INVALID_HANDLE_VALUE\n") ;

	if (hDevNames != INVALID_HANDLE_VALUE && hDevNames != NULL)
		{
		LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(hDevNames) ;
		TRACE("------hDevNames--------------------------\n") ;
		TRACE("wDriverOffset   : %d\n", lpDevNames->wDriverOffset) ;
		TRACE("wDeviceOffset   : %d\n", lpDevNames->wDeviceOffset) ;
		TRACE("wOutputOffset   : %d\n", lpDevNames->wOutputOffset) ;
		TRACE("wDefault        : %x\n", lpDevNames->wDefault) ;
		TRACE("DriverName      : %s\n", (char*)((char*)lpDevNames + lpDevNames->wDriverOffset)) ;
		TRACE("DeviceName      : %s\n", (char*)((char*)lpDevNames + lpDevNames->wDeviceOffset)) ;
		TRACE("OutputName      : %s\n", (char*)((char*)lpDevNames + lpDevNames->wOutputOffset)) ;
		::GlobalUnlock(hDevNames) ;
		}
	else
		TRACE("hDevNames            : INVALID_HANDLE_VALUE\n") ;
	TRACE("===================Dump Complete=============================\n") ;
}
#endif
