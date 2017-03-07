/***************************************************************
* C file:  Tstdll32.c... for Tstdll32.exe
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
* History:
*  June 12 96: fixed misdeclaration for wincpufeatures() -- now a DWORD
*            : added message for MMX(TM) Technology processors
*  Aug 96    : added check for missing dll.  
*
***************************************************************/

#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "tstdll32.h"
#include "resource.h"



HINSTANCE hLibrary;				//handle for cpuinf32 dll

WORD (FAR *lpfnwincpuid)();
WORD (FAR *lpfnwincpuidsupport)();
WORD (FAR *lpfnwincpuidext)();
DWORD (FAR *lpfnwincpufeatures)();
ushort(FAR PASCAL *lpfngetdllversion)();
struct TIME_STAMP (FAR *lpfnwinrdtsc)();
struct FREQ_INFO  (FAR *lpfnwincpuspeed)(int BSFclocks);

HWND	hWnd;
HDC	 	hDC;

#if !defined (APIENTRY)
		#define	APIENTRY pascal
#endif


        // The name of this application
#define APPCLASSNAME "tstdll32"



HINSTANCE hInst;
char szAppName[] = "tstdll32";
char szAppIconName[] = "test32icon";
char szTitle[]   = "32-bit dll test";
char szAppClass[32];


/***************************************************************
* WinMain()
*
* Inputs:
*	hInstance		Main window handle instance
*	hPrevInstance	Previous window handle instance
*	lpCmdLine		Pointer to command line string
*	nCmdShow		Window display flag
*
* Results:
*	return value of the PostQuitMessage function if the function
*	   is successful.
*	return NULL if it terminates before entering the message 
*      loop.            
***************************************************************/

int APIENTRY WinMain ( HINSTANCE hInstance, 
					   HINSTANCE hPrevInstance,
               		   LPSTR lpCmdLine, int nCmdShow )
{
		char buf[512]="";		// String Variable for 
									//   Message Boxes

	//Load CPUINF32.DLL and do CPUID
	if (LoadLibrary(CPUINFODLL)==NULL) {

		if (LOBYTE(LOWORD(GetVersion()))<4) {
				
			return (FALSE);					// if DLL not found exit app
			}
		else {
			sprintf(buf, "CPUINF32.DLL not found");
	   		MessageBox(NULL,buf,"Error", MB_ICONINFORMATION); 
			return (FALSE);					// if DLL not found exit app
			}
	}//if
	else {
	
    
	sprintf( szAppClass, "%s%d", APPCLASSNAME, hInstance);
	if (!InitApplication( hInstance)) {
		return (FALSE);
	}
	// Initialization for specific instance
	if (!InitInstance(hInstance, nCmdShow)) {
		return (FALSE);
	}
    EventLoop(hInstance);
	return 0;

	lpCmdLine;
   }
} // WinMain()



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

BOOL InitApplication( HINSTANCE hInstance)
{	// called for first instance of app
	WNDCLASS  wc;

	wc.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC);
	
	wc.lpfnWndProc   = (WNDPROC)WndProc;	// Window Procedure
	
	wc.cbClsExtra    = 0;					// No per-class 
											//   extra data.
	
	wc.cbWndExtra    = (int)NULL;			// 4-bytes extra 
											//   data.
	
	wc.hInstance     = hInstance;			// Owner of this
											//   class
	
	wc.hIcon         = LoadIcon (hInstance, szAppIconName);	
											// Icon name from 
											//   .RC
	
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW); 	
											// Cursor
	
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);		
											// Default color
	
	wc.lpszMenuName  = szAppName;			// Menu name from
											//   .RC file
	
	wc.lpszClassName = szAppClass;			// Name to register
											//   as

	return (RegisterClass(&wc));
} // InitApplication()



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

BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
	HWND    wHdl;


	hInst = hInstance; 			// Save instance handle
								
								// Main window for this app 
								//   instance.
	wHdl = CreateWindow(
		szAppClass,	        	// See RegisterClass()
		szTitle,	        	// Window title bar
		WS_OVERLAPPEDWINDOW,	// Window style.
		CW_USEDEFAULT,			// Init x pos
		CW_USEDEFAULT,			// Init y pos
		CW_USEDEFAULT,			// Init x size
		CW_USEDEFAULT,			// Init y size
		
		NULL,		        	// Overlapped windows have no 
								//   parent.
		
		NULL,		        	// Use the window class menu.
		
		hInstance,	        	// This instance owns this 
								//   window.
		
		NULL		        	// We don't use any data in our
								//   WM_CREATE
	);


	// Make the window visible; update its client area; 
	//   and return "success"
	
	ShowWindow(wHdl, nCmdShow); // Show the window
	UpdateWindow(wHdl);			// Sends WM_PAINT message

	hWnd = wHdl;				// Used in actions.c
	return (TRUE);				// We succeeded...

} // InitInstance()



/***************************************************************
* EventLoop()
*
* Inputs:
*	hInstance	Window instance handle
*
* Returns: none
***************************************************************/

void EventLoop(HINSTANCE hInstance)
{
	MSG	 msg;
 	HANDLE hAccel;

	hAccel=LoadAccelerators(hInstance, szAppName);
    while (GetMessage(&msg, 	// Message structure
		      NULL,   			// Handle of window receiving 
		      					//   the message
		      0,      			// Lowest message to examine
		      0))     			// Highest message to examine
    {
	
	if (!TranslateAccelerator (hWnd,hAccel, &msg)) {
	TranslateMessage(&msg);		// Translates virtual key codes
	DispatchMessage(&msg); 		// Dispatches message to window
	}

    }
} // EventLoop()       


void GetSpeed( int iType )
{
	WORD	cpu_type   = 0;	// CPU Family variable
	WORD	extensions = 0; // CPU Extensions variable
	DWORD	features   = 0;	// CPU Features variable
	
    ushort	version	   = 0; // CPUINFO DLL Version

	struct FREQ_INFO cpu_speed;		// Return variable 
											//   structure for 
											//   cpuspeed 
											//   routine
			
	char buf[512]="";		// String Variable for 
									//   Message Boxes
	
  	
	
	int u1,u2,exact;		// Statistical variables for
	int d1,d2;				//   raw frequency analysis
		 
	float per1,per2,per3;	// Statistical Percentages

    ulong norm_freq, raw_freq;        // Previous Normalized 
    								//   Frequency
    	
    int missed=0;			// Keeps track of whether 
    								//   any speeds more than
        							//   3 MHz from the 
        							//   normalized occurred
		
   	LARGE_INTEGER start, end;	// Variables to delay
	ulong time;					//   determine average
										//    per test 

	int i, response;			// Variable for processing
									//   MessageBox responses
				

	hLibrary=LoadLibrary(CPUINFODLL);

	(FARPROC) lpfnwincpuspeed = 
			GetProcAddress(hLibrary,"cpuspeed");
				
	cpu_speed = (*lpfnwincpuspeed)(iType);
				
	if ( cpu_speed.in_cycles == 0 && cpu_speed.ex_ticks  == 0 ) {
					 
		 sprintf(buf,
			 	"This processor cannot be accurately "
			 	"timed with this program.\n The "
			 	"processor is either an Intel Clone "
			 	"or is below 80386 level.");
		 MessageBox(NULL,buf,"error", MB_ICONINFORMATION );
	}

	sprintf(buf,
			"Clock Cycles: %lu cycles\n"
			"Elapsed Time: %luus\n"
			"Raw Clock Frequency: %luMHz\n"
			"Normalized Frequency: %luMHz",
			cpu_speed.in_cycles,
			cpu_speed.ex_ticks,
			cpu_speed.raw_freq,
			cpu_speed.norm_freq);          

	MessageBox(NULL,buf,"32-bit cpuspeed", 
				MB_ICONINFORMATION );

	if ( iType == -1 )	// If Cmos time, then return because too slow
		return;

	sprintf(buf,
			"Would you like to perform\n"
			"  a 1000 iteration test?");

	response = MessageBox(NULL,buf,"test", 
			MB_YESNO|MB_ICONQUESTION );
				
	if ( response == IDNO ) {
			
		FreeLibrary(hLibrary);
		return;
    }
        
	// Testing Code.... Runs 100 times and does 
	//   statistical analysis on the data returned.
	//	   --BEGIN--
			
	norm_freq = cpu_speed.norm_freq;
	raw_freq = cpu_speed.raw_freq;
	u2=0;
	u1=0;
	exact=0;
	d1=0;
	d2=0;

	QueryPerformanceCounter(&start);

	for ( i = 0; i<1000; i++ ) {

   		cpu_speed = (*lpfnwincpuspeed)(iType);
					        
		switch ( (int)cpu_speed.norm_freq - 
				 (int)norm_freq ) {
						
			case 0:
				exact++;
				break;
						
			case 1:
				u1++;
				break;
						
			case 2:
				u2++;
				break;
						
			case -1:
				d1++;
				break;
					
			case -2:
				d2++;
				break;
					
			default:
				missed++; // Set missed flag; deviate more than 3Mhz
		}
	}
				
	QueryPerformanceCounter(&end);
				
	time = (ulong) (end.LowPart - start.LowPart);
	time = time / 1193180;

	per1 = (float)((float)exact/10.0);
				
	per2 = (float)((float)(u1+d1)/10.0);
				
	per3 = (float)((float)(u2+d2)/10.0);

	sprintf(buf,
			"%luMHz\t%luMHz\t%luMHz\t%luMHz\t%luMHz\n"
			"  %03d\t  %03d\t  %03d\t  %03d\t  %03d\t"
			"\n\n"
			"Exact value  \t: %.2f\n"
			"Within 1 MHz \t: %.2f\n"
			"Within 2 MHz \t: %.2f\n\n"
		    "Beyond 2 MHz \t: %.2f\n\n"
		    "----->  Normalized Speed  \t=  %lu\n"
			"----->    Raw Speed       \t=  %lu\n\n"
			"   Delay per test = %dms",
			norm_freq-2,norm_freq-1,norm_freq,norm_freq+1,norm_freq+2,d2,d1,
			exact,u1,u2,per1,per2,per3,0.0,
			norm_freq,raw_freq,time);
				
	MessageBox(NULL,buf,"32-bit cpuspeed",
				MB_ICONINFORMATION );

	//		--END--
	// Testing Code.... Ran 100 times and did 
	//   statistical analysis on the data returned.
												   
	FreeLibrary(hLibrary);
}


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

LRESULT CALLBACK WndProc(
      HWND hWnd,         		// Window handle
      UINT message,      		// Type of message
      WPARAM uParam,     		// Additional information
      LPARAM lParam      		// Additional information
      )
{								// Message Handler
	PAINTSTRUCT	ps;                                         
    
	switch (message) {
		
		case WM_CREATE:
			hDC = GetDC( hWnd);
			break;
	
		case WM_SIZE:
			break ;

		case WM_PAINT:
			hDC=BeginPaint(hWnd,&ps);
			EndPaint(hWnd,&ps);
			break;

    	case WM_CLOSE:
        	return (DefWindowProc(hWnd,message,uParam,lParam));
	    	break;

    	case WM_DESTROY:	// Message: window being destroyed
        	PostQuitMessage(0);
        	break;

 		case WM_COMMAND:	// Message: command from application 
 							//   menu
		{
   		
			WORD	cpu_type   = 0;	// CPU Family variable
			WORD	extensions = 0; // CPU Extensions variable
			DWORD	features   = 0;	// CPU Features variable
	
	        ushort	version	   = 0; // CPUINFO DLL Version

	        int major, minor;		// Variables for storing DLL
	        						//   version

			char buf[512]="";		// String Variable for 
									//   Message Boxes
	
    	
    		int missed=0;			// Keeps track of whether 
    								//   any speeds more than
        							//   3 MHz from the 
        							//   normalized occurred
		
			char misses[256]= "";	// Keeps track of all raw 
									//   speeds more than 3 MHz
									//   from the normalized 
									//   value

    		struct TIME_STAMP stamp;	
    								// Variable for 64-bit Time
    								//   Stamp read

	   	    int cpuid_support;		// Flag to determine whether
    	    						//   CPUID opcode is 
    	    						//   supported

    	
    		WORD wmId, wmEvent;
	    
	    	wmId    = LOWORD(uParam);
	    	wmEvent = HIWORD(uParam);
     	
			switch(LOWORD(uParam)) {


            case IDM_EXIT:
	        
	        	SendMessage(hWnd, WM_CLOSE, 0, 0l);
	        	break;


			case IDM_CPUID:

				hLibrary=LoadLibrary(CPUINFODLL);
			
				(FARPROC) lpfnwincpuid = 
						GetProcAddress(hLibrary,"wincpuid");
				(FARPROC) lpfnwincpuidsupport =
						GetProcAddress(hLibrary,
							"wincpuidsupport");
				
				cpu_type = (*lpfnwincpuid)();
				cpuid_support = (*lpfnwincpuidsupport)();

				FreeLibrary(hLibrary);

			    if ( cpu_type & CLONE_MASK )
			    	sprintf(buf,"Intel Clone CPU Family : %x",
			    		cpu_type);

				else if ( cpuid_support )	
									// Intel processor presence 
									//   can only be verified if
									//   CPUID opcode is 
									//   supported and the 
									//   GenuineIntel vendor ID 
									//   is read.
												
					sprintf(buf,"Intel CPU Family : %x",
						cpu_type);
				
				else
					sprintf(buf,"CPU Family : %x", cpu_type);
			
				MessageBox(NULL,buf,"wincpuid",
					MB_ICONINFORMATION);
				
				break;

		case IDM_CPUID2:

				hLibrary=LoadLibrary(CPUINFODLL);           
				
				(FARPROC) lpfnwincpuidext = 
						GetProcAddress(hLibrary,"wincpuidext");
				
				extensions = (*lpfnwincpuidext)();
   
   				FreeLibrary(hLibrary);

				sprintf(buf,"Type/Family/Model/Stepping: %.4x",
						extensions);
				
				MessageBox(NULL,buf,"wincpuidext",
					MB_ICONINFORMATION);

				break;

		case IDM_CMOSSPEED:
			{
				int response;

				response = MessageBox(NULL,"This feature is not supported for NT; do you want to continue?","test", 
									MB_YESNO|MB_ICONQUESTION );
				
				if ( response == IDYES ) {
					GetSpeed( -1 );
				}
			}
			break;

		case IDM_CPUSPEED:
				GetSpeed( 0 );
				break;


		case IDM_FEATUREFLAGS:

				hLibrary=LoadLibrary(CPUINFODLL);
				
				(FARPROC) lpfnwincpufeatures = 
						GetProcAddress(hLibrary,
						"wincpufeatures");
				
				features = (*lpfnwincpufeatures)();
		
			/*Print extra line in message for MMX(TM) technology processor, ie, features(23)=1*/
				if (features & 0x00800000) //then MMX(TM) technology
				 sprintf(buf,
				   "Feature Flags: %.8x \n on a processor with MMX(TM) technology", features);
				else 
				 sprintf(buf,"Feature Flags: %.8x",features);		
				/***************************/

				
				MessageBox(NULL,buf,"wincpufeatures",
					MB_ICONINFORMATION);
				FreeLibrary(hLibrary);
				break;

		case IDM_READ:
				
				hLibrary=LoadLibrary(CPUINFODLL);
				(FARPROC) lpfnwinrdtsc = 
					GetProcAddress(hLibrary,"winrdtsc");
					
				stamp=(*lpfnwinrdtsc)();
				
				if ( stamp.High != 0 || stamp.Low != 0 ) {
				
					sprintf(buf,"Time Stamp: %08lx  %08lx",
						stamp.High,stamp.Low);
					
					MessageBox(NULL,buf,"winrdtsc",
						MB_ICONINFORMATION);
                
                }
				else {
					
					MessageBox(NULL,"Time Stamping not "
						"available on this system","error",
						MB_ICONINFORMATION);
				
				}
		        
				FreeLibrary(hLibrary);
				break;
			

		case IDM_GETDLLVERSION:
			
				hLibrary=LoadLibrary(CPUINFODLL);
				(FARPROC) lpfngetdllversion =
					GetProcAddress(hLibrary,"getdllversion");
					
				version = (*lpfngetdllversion)();
				
				major = version >> 8;		// Shift out minor
											//   version.
											
				minor = version - major*256;	// Subtract off
												//   major 
												//   version.
				
				sprintf(buf,"CPUINFO32 DLL Version: %x.%x",
					major,minor);
				
				MessageBox(NULL,buf,"getdllversion",
					MB_ICONINFORMATION);
				
				FreeLibrary(hLibrary);	
				break;

		}
	}

    default:          // Passes it on if unproccessed
         return (DefWindowProc(hWnd, message, uParam, lParam));
	}

    return (0);
}

