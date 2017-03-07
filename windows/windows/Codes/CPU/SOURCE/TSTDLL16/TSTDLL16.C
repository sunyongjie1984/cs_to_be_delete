/***************************************************************
* C file:  Tstdll16.c... for Tstdll16.exe
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
 
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <string.h>

#include "tstdll16.h"
#include "resource.h"


HINSTANCE hLibrary;				// Handle for cpuinf16 dll

WORD  (FAR PASCAL *lpfnwincpuid)();
WORD  (FAR *lpfnwincpuidsupport)();
WORD  (FAR PASCAL *lpfnwincpuidext)();
DWORD (FAR PASCAL *lpfnwincpufeatures)();
ushort(FAR PASCAL *lpfngetdllversion)();
struct TIME_STAMP (FAR PASCAL *lpfnwinrdtsc)();
struct FREQ_INFO  (FAR PASCAL *lpfnwincpuspeed)(int BSFclocks);

HWND	hWnd;
HDC	 	hDC;

#if !defined (APIENTRY)
		#define APIENTRY far pascal
#endif

#define APPCLASSNAME "tstdll16"
HINSTANCE hInst;
char szAppName[] = "tstdll16";
char szAppIconName[] = "tstdll16icon";
char szTitle[]   = "16-bit dll test";
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
	
	wc.cbWndExtra    = NULL;				// 4-bytes extra 
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
	        						
			struct FREQ_INFO cpu_speed;		// Return variable 
											//   structure for 
											//   cpuspeed 
											//   routine
			
			char buf[512]="";		// String Variable for 
									//   Message Boxes
	
			int i;					// Temp. Counter variable
  	
			ulong speed;			// Temp. variable to store 
									//   frequency
	
			int u1,u2,exact;		// Statistical variables for
			int d1,d2;				//   raw frequency analysis
		
		  	float per1,per2,per3;	// Statistical Percentages

    		ulong prev_freq;        // Previous Normalized 
    								//   Frequency
    	
    		int missed=0;			// Keeps track of whether 
    								//   any speeds more than
        							//   3 MHz from the 
        							//   normalized occurred
		
			char misses[256]= "";	// Keeps track of all raw 
									//   speeds more than 3 MHz
									//   from the normalized 
									//   value
                                    
 	    	DWORD start, end;		// Variables to determine 
 	    	int time;				//   average delay per test
		
			int response;			// Variable for processing
									//   MessageBox responses
				
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
			    
				MessageBox(NULL,buf,"wincpuid",0);

				break;


		case IDM_CPUID2:

				hLibrary=LoadLibrary(CPUINFODLL);           
				
				(FARPROC) lpfnwincpuidext = 
						GetProcAddress(hLibrary,"wincpuidext");
				
				extensions = (*lpfnwincpuidext)();

				FreeLibrary(hLibrary);

				sprintf(buf,"Type/Family/Model/Stepping: %.4x",
						extensions);
				
				MessageBox(NULL,buf,"wincpuidext",0);

				break;
				
		case IDM_CMOSSPEED:

				hLibrary=LoadLibrary(CPUINFODLL);

				(FARPROC) lpfnwincpuspeed = 
						GetProcAddress(hLibrary,"cpuspeed");
				
				cpu_speed = (*lpfnwincpuspeed)(-1);
				
				if ( cpu_speed.in_cycles == 0 &&
					 cpu_speed.ex_ticks  == 0 ) {
					 
					 sprintf(buf,
					 	"This processor cannot be accurately "
					 	"timed with this program.\n The "
					 	"processor is either an Intel Clone "
					 	"or is below 80386 level.");
					MessageBox(NULL,buf,"error", 
						MB_ICONINFORMATION );
					
					FreeLibrary(hLibrary);
					return (0);
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
				
				MessageBox(NULL,buf,"16-bit cpuspeed", 
						MB_ICONINFORMATION );

				FreeLibrary(hLibrary);
				
				break;

		case IDM_CPUSPEED:
				
				hLibrary=LoadLibrary(CPUINFODLL);

				(FARPROC) lpfnwincpuspeed = 
						GetProcAddress(hLibrary,"cpuspeed");
				
				cpu_speed = (*lpfnwincpuspeed)(0);
				
				if ( cpu_speed.in_cycles == 0 &&
					 cpu_speed.ex_ticks  == 0 ) {
					 
					 sprintf(buf,
					 	"This processor cannot be accurately "
					 	"timed with this program.\n The "
					 	"processor is either an Intel Clone "
					 	"or is below 80386 level.");
					MessageBox(NULL,buf,"error", 
						MB_ICONINFORMATION );
					
					FreeLibrary(hLibrary);
					return (0);
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
				
				MessageBox(NULL,buf,"16-bit cpuspeed", 
						MB_ICONINFORMATION );
				
								
				sprintf(buf,
					"Would you like to perform\n"
					"  a 100 iteration test?");
				
				response = MessageBox(NULL,buf,"test", 
						MB_YESNO|MB_ICONQUESTION );
				
				if ( response == IDNO ) {
					
					FreeLibrary(hLibrary);
					return(0);
                    
                }
        
                
				// Testing Code.... Runs 100 times and does 
				//   statistical analysis on the data returned.
				//	   --BEGIN--
				
				prev_freq = cpu_speed.norm_freq;
	
				u2=0;
				u1=0;
				exact=0;
				d1=0;
				d2=0;
				
				start = timeGetTime();	// Get starting time for
										//   the following 100
										//   tests to later
										//   determine average
										//   delay per test.
				
				for ( i = 0; i<100; i++ ) {
                
		    		cpu_speed = (*lpfnwincpuspeed)(0);
						        
			        if ( (int)cpu_speed.norm_freq != 
			        	 (int)prev_freq ) {
			        
			            sprintf(buf,
			            	"Previous Frequency was %lu\n"
			            	"Current Frequency is %lu\n"
					    	"Statistical Information "
					    	"will be incorrect.\n\n"
					    	"Continue?", prev_freq,
					    	cpu_speed.norm_freq);
					    	
					    response = MessageBox(NULL,buf,"error",
					    		MB_ICONQUESTION|MB_YESNO);
					    
					    if ( response == IDNO ) {
					    	
					    	FreeLibrary (hLibrary);
					    	return(0);
					    }
					    
					}
					
					prev_freq = cpu_speed.norm_freq;
					
					switch ( (int)cpu_speed.raw_freq - 
							 (int)cpu_speed.norm_freq ) {
						
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
 							sprintf(misses,"%s %02d\t",misses,
									((int)cpu_speed.raw_freq-
									 (int)cpu_speed.norm_freq));
							
							missed = 1; // Set missed flag
							
							if ( strlen ( misses ) >= 240 ) {
										// If queue gets too
										//   large, dump data
								sprintf(buf,
									"The following raw speeds"
									" deviated more than 3 MHz"
									"\nfrom their normalized "
								 	"values:\n\n%s\n\n"
								 	"More Deviations may "
								 	"follow\n Continue?",
								 	misses);
								
								response = MessageBox(NULL,buf,
									"deviations",
									MB_YESNO);
								
								if ( response == IDNO ) {
								
									FreeLibrary(hLibrary);
									return (0);
								}

								misses[0] = '\0'; // Reset queue
								missed = 0;		  //   and flag
							}
					}
				}
				
				FreeLibrary(hLibrary);

				end = timeGetTime();		// Get ending time
				time = (int) (end - start); //   for last 100
				time = time / 100;			//   tests and 
											//   average them.
											
				
				speed = cpu_speed.norm_freq;
                                            
                
                                         	// Calculate 
                                         	//   statistical 
                                         	//   information
				per1 = (float) (float)exact;
				
				per2 = (float) ((float)exact+(float)u1+
							(float)d1);
				
				per3 = (float) ((float)exact+(float)u1+
							(float)u2+(float)d1+(float)d2);

				
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
					speed-2,speed-1,speed,speed+1,speed+2,d2,d1,
					exact,u1,u2,per1,per2,per3,(100-per3),
					speed,cpu_speed.raw_freq,time);
				
				MessageBox(NULL,buf,"16-bit cpuspeed",
					MB_ICONINFORMATION );

				if ( missed ) {
					
					sprintf(buf,
						"The following raw speeds deviated more"
						" than 3 MHz\n from their normalized "
						"values:\n%s",misses);
					
					MessageBox(NULL,buf,"deviations",
							MB_ICONINFORMATION);
					}
                
                
				//		--END--
				// Testing Code.... Ran 100 times and did 
				//   statistical analysis on the data returned.
												   
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
				   "Feature Flags: %.8lx \n on a processor with MMX(TM) technology", features);
				else 
				 sprintf(buf,"Feature Flags: %.8lx",features);		
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

				FreeLibrary(hLibrary);
				
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
		        
				break;
		        
		
		case IDM_GETDLLVERSION:
			
				hLibrary=LoadLibrary(CPUINFODLL);
				(FARPROC) lpfngetdllversion =
					GetProcAddress(hLibrary,"getdllversion");
					
				version = (*lpfngetdllversion)();
				
				FreeLibrary(hLibrary);
								
				major = version >> 8;		// Shift out minor
											//   version.
											
				minor = version - major*256;	// Subtract off
												//   major 
												//   version.
				
				sprintf(buf,"CPUINFO16 DLL Version: %x.%x",
					major,minor);
				
				MessageBox(NULL,buf,"getdllversion",
					MB_ICONINFORMATION);
				
				break;
		}
	}

    default:          // Passes it on if unproccessed
         return (DefWindowProc(hWnd, message, uParam, lParam));
	}

    return (0);

} // WndProc()

