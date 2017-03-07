/***************************************************************
* C file:  Tstdll16.h... for Tstdll16.exe
*
*       This program has been developed by Intel Corporation.  
*		You have Intel's permission to incorporate this code 
*       into your product, royalty free.  Intel has various 
*	    intellectual property rights which it may assert under
*       certain circumstances, such as if another manufacturer's
*       processor mis-identifies itself as being "GenuineIntel"
*		when the CPUID instruction is executed.
*
*       Intel specifically disclaims all warranties, express or
*       implied, and all liability, including consequential and
*		other indirect damages, for the use of this code, 
*		including liability for infringement of any proprietary
*		rights, and including the warranties of merchantability
*		and fitness for a particular purpose.  Intel does not 
*		assume any responsibility for any errors which may 
*		appear in this code nor any responsibility to update it.
*
*  * Other brands and names are the property of their respective
*    owners.
*
*  Copyright (c) 1995, Intel Corporation.  All rights reserved.
***************************************************************/



#ifndef tstdll16_h
#define tstdll16_h

// Specify dll filename for functions under test.
#define CPUINFODLL	"cpuinf16.dll"

#ifdef __WINDOWS_386__
#define _EXPORT
#else
#define _EXPORT __export
#endif



// VARIABLE STRUCTURE DEFINITIONS //////////////////////////////
struct FREQ_INFO
{
	unsigned long in_cycles;	// Internal clock cycles during
								//   test
								
	unsigned long ex_ticks;		// Microseconds elapsed during 
								//   test
								
	unsigned long raw_freq;		// Raw frequency of CPU in MHz
	
	unsigned long norm_freq;	// Normalized frequency of CPU
								//   in MHz.
};

struct TIME_STAMP
{
	DWORD High;					// Upper 32-bits of Time Stamp
								//   Register value
	
	DWORD Low;					// Lower 32-bits of Time Stamp
};								//   Register value



typedef unsigned short ushort;
typedef unsigned long  ulong;
	
// CONSTANT DEFINITIONS ////////////////////////////////////////
#define CLONE_MASK		0x8000	// Mask to be 'OR'ed with proc-
								//   essor family type

/***************************************************************
* InitApplication()
*
* Inputs:
*	hInstance	Handle for first instance of app
*
* Returns:
*	atom that uniquely identifies the class being registered.
*	zero if an error occurs.
***************************************************************/
BOOL InitApplication(HANDLE);


/***************************************************************
* InitInstance()
* 
* Purpose:
*   Initialization for first instance of app.
*
* Inputs:
*	hInstance	Main window handle instance 
*	nCmdShow	Main window display flag
*
* Returns:
*	Always returns true.
***************************************************************/
BOOL InitInstance(HANDLE, int);


/***************************************************************
* EventLoop()
*
* Inputs:
*	hInstance	Window instance handle
*
* Returns: none
***************************************************************/
void EventLoop();


/***************************************************************
* WndProc(HWND, UINT, WPARAM, LPARAM)
*
* Purpose:
*   Processes messages
*
* Messages:
*    WM_COMMAND    - application menu (About dialog box)
*    WM_DESTROY    - destroy window
*
* Inputs:
*   hWnd		Window Handle
*   message		Type of Message
*   uParam		Additional Information
*	LParam		Additional Information
*
* Returns:
*   LRESULT returned by DefWindowProc or 0
***************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif tstdll16_h
