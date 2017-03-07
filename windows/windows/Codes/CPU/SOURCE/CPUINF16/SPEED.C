/***************************************************************
* C file:  Speed.c... for cpuinf16 DLL
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
#include <math.h>
#include <stdio.h>
#include <mmsystem.h>
#include <limits.h>    
#include <memory.h>

#include "speed.h"
#include "cpuid.h"

// Tabs set at 4
#define ROUND_THRESHOLD		6

// Tabs set at 4
static struct FREQ_INFO GetCmosCpuSpeed();
static struct FREQ_INFO GetRDTSCCpuSpeed();
static struct FREQ_INFO GetBSFCpuSpeed(ulong cycles);
static unsigned long diffTime64(unsigned long t1Hi, unsigned long t1Low, 
						 unsigned long t2Hi, unsigned long t2Low, 
 					 	 unsigned long *tHi, unsigned long *tLow );

// extern in ASM file
ushort Time_Processor_bsf(void);

/***************************************************************
* LibMain() -- Windows entry procedure for DLLSs
* 
***************************************************************/
int FAR PASCAL _export LibMain(HANDLE hI, WORD wDS, WORD cbHS, LPSTR lpszCL) {
	if (cbHS != 0) 
	
		UnlockData(0);
	
	return 1;
} // LibMain()



/***************************************************************
* WEP() -- Windows exit procedure for the DLLs.
*
***************************************************************/
int FAR PASCAL _export WEP(int nParam) {
	return 1;
} // WEP()



/***************************************************************
* CpurawSpeed() -- Return the raw clock rate of the host CPU.
*
* Inputs:
*	clocks:		0: Use default value for number of cycles
*				   per BSF instruction.
*               -1: Use CMos timer to get cpu speed (DOES NOT WORK FOR WINNT).
*   			Positive Integer: Use clocks value for number
*				   of cycles per BSF instruction.
*
* Returns:
*		If error then return all zeroes in FREQ_INFO structure
*		Else return FREQ_INFO structure containing calculated 
*       clock frequency, normalized clock frequency, number of 
*       clock cycles during test sampling, and the number of 
*       microseconds elapsed during the sampling.
***************************************************************/

unsigned long FAR PASCAL cpurawspeed(int clocks)
{
	struct FREQ_INFO cpu_speed;

	cpu_speed = cpuspeed(clocks);
	return cpu_speed.raw_freq;
}

/***************************************************************
* CpunormSpeed() -- Return the raw clock rate of the host CPU.
*
* Inputs:
*	clocks:		0: Use default value for number of cycles
*				   per BSF instruction.
*               -1: Use CMos timer to get cpu speed.
*   			Positive Integer: Use clocks value for number
*				   of cycles per BSF instruction.
*
* Returns:
*		If error then return all zeroes in FREQ_INFO structure
*		Else return FREQ_INFO structure containing calculated 
*       clock frequency, normalized clock frequency, number of 
*       clock cycles during test sampling, and the number of 
*       microseconds elapsed during the sampling.
***************************************************************/

unsigned long FAR PASCAL cpunormspeed(int clocks)
{
	struct FREQ_INFO cpu_speed;

	cpu_speed = cpuspeed(clocks);
	return cpu_speed.norm_freq;
}

/***************************************************************
* ProcessorCount() -- Return the number of CPU's on this machine.
*
* Inputs:
*
* Returns:
*		 always 1 for 16 bit dll
***************************************************************/

unsigned long FAR PASCAL ProcessorCount()
{
	return 1;
}

/***************************************************************
* CpuSpeed() -- Return the raw clock rate of the host CPU.
*
* Inputs:
*	clocks:		NULL: Use default value for number of cycles
*				   per BSF instruction.
*   			Positive Integer: Use clocks value for number
*				   of cycles per BSF instruction.
*
* Returns:
*		If error then return all zeroes in FREQ_INFO structure
*		Else return FREQ_INFO structure containing calculated 
*       clock frequency, normalized clock frequency, number of 
*       clock cycles during test sampling, and the number of 
*       microseconds elapsed during the sampling.
***************************************************************/

struct FREQ_INFO FAR PASCAL cpuspeed(int clocks) 
{
	ulong  cycles;					// Clock cycles elapsed 
									//   during test
	
	ushort processor = wincpuid();	// Family of processor

	DWORD features = wincpufeatures();	// Features of Processor
	
	int manual=0;			// Specifies whether the user 
							//   manually entered the number of
							//   cycles for the BSF instruction.

	struct FREQ_INFO cpu_speed;		// Return structure for
									//   cpuspeed
					
	// Number of cycles needed to execute a single BSF 
	//   instruction. Note that processors below i386(tm) 
	//   are not supported.
	ushort processor_cycles[] = {
		00,  00,  00, 115, 47, 43, 
		38,  38,  38, 38,  38, 38, 
	};

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));
	
	if ( processor & CLONE_MASK )
		return cpu_speed;

	// Check for manual BSF instruction clock count
	if (0 <= clocks) {
		cycles =ITERATIONS*(ulong)processor_cycles[processor];
	}
	else if (0 < clocks && clocks <= MAXCLOCKS)  {
		cycles = ITERATIONS * (ulong) clocks;
		manual = 1;			// Toggle manual control flag.
							//   Note that this mode will not
							// 	 work properly with processors
							//   which can process multiple
							//   BSF instructions at a time.
							//   For example, manual mode
							//   will not work on a 
							//   PentiumPro(R)
	}

	if ( ( features&0x00000010 ) && !(manual) ) {
		if ( clocks == 0 )
			return GetRDTSCCpuSpeed();
		else
			return GetCmosCpuSpeed();	
    }
	else if ( processor >= 3 ) {
		return GetBSFCpuSpeed(cycles);
	}        
 
	return cpu_speed;
   	
} // cpuspeed()



static struct FREQ_INFO GetBSFCpuSpeed(ulong cycles)
{
 	ulong  ticks;	// Microseconds elapsed 								//   during test
	ulong freq;		// Most current frequ. calculation
	int i;			// Temporary Variable

	ulong current = 0;      // Variable to store time
							//   elapsed during loop of
							//   of BSF instructions

	ulong lowest  = ULONG_MAX;	// Since algorithm finds 
								//   the lowest value out of
								//   a set of samplings, 
								//   this variable is set 
								//   intially to the max 
								//   unsigned long value). 
								//   This guarantees that 
								//   the initialized value 
								//   is not later used as 
								//   the least time through 
								//   the loop.

	struct FREQ_INFO cpu_speed;		// Return structure for
									//   cpuspeed
					
	memset(&cpu_speed, 0x00, sizeof(cpu_speed));
	
	for ( i = 0; i < SAMPLINGS; i++ ) {
								// Sample SAMPLINGS times. 
								//   Can be increased or 
								//   decreased depending
								//   on accuracy vs. time
								//   requirements

			
		current = Time_Processor_bsf();
           
		if ( current < lowest )		// Take lowest elapsed
			lowest = current;		//   time to account
									//   for some samplings
									//   being interrupted
									//   by other operations 
	}

	ticks = lowest;				
		
		
	// Note that some seemingly arbitrary mulitplies and
	//   divides are done below. This is to maintain a 
	//   high level of precision without truncating the 
	//   most significant data. According to what value 
	//   ITERATIIONS is set to, these multiplies and
	//   divides might need to be shifted for optimal
	//   precision.

    ticks = ticks * 100000; 	// Convert ticks to hundred 
      							//   thousandths of a tick
        
    ticks = ticks / 119318;		// Convert hundred 
       							//   thousandths of ticks to
       							//   microseconds (us)
        
    if ( (ticks%119318) >= 119318/2 )
       	ticks++;				// Round up if necessary
        	
    freq = cycles/ticks;		// Cycles / us  = MHz

	cpu_speed.raw_freq  = freq;
    if ( cycles%ticks > ticks/2 )
       	freq++;					// Round up if necessary

	cpu_speed.in_cycles = cycles;	// Return variable structure
	cpu_speed.ex_ticks  = ticks;	//   determined by one of 
	cpu_speed.norm_freq = freq;

	return cpu_speed;
}			

static struct FREQ_INFO GetRDTSCCpuSpeed()
{
 	ulong  total_ticks=0, ticks;	// Microseconds elapsed 
									//   during test
	
	ulong  total_cycles=0, cycles;	// Clock cycles elapsed 
									//   during test
	
	ulong  stamp0, stamp1;			// Time Stamp Variable 
									//   for beginning and end 
    
    ushort u0,u1;     		        // 16-bit variables for time
    ushort v0,v1;					//   stamp reads. These are 
    								//   later merged into 
    								//   stamp0, and stamp1 
    								//   (32-bit variables)

	ulong freq;				// Most current frequ. calculation
	ulong freq2;			// 2nd most current frequ. calc.
	ulong freq3;			// 3rd most current frequ. calc.
	
	ulong total;			// Sum of previous three frequency
							//   calculations

	int manual=0;			// Specifies whether the user 
							//   manually entered the number of
							//   cycles for the BSF instruction.

	int tries=0;			// Number of times a calculation has
							//   been made on this call to 
							//   cpuspeed

	struct FREQ_INFO cpu_speed;		// Return structure for
									//   cpuspeed
					
    DWORD t0,t1;                   	// Variables to store 
    								//   timeGetTime values

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));

	// On Pentium Processors or above use 
	//   the Read Time Stamp method which 
	//   compares elapsed time on from the
	//   timeGetTime call with elaped
	//   cycles on the Time Stamp Register.

    do {			// This do loop runs up to 20 times or
    				//   until the average of the previous 
    				//   three calculated frequencies is 
    				//   within 2 MHz of each of the 
    				//   individual calculated frequencies. 
					//   This resampling increases the 
					//   accuracy of the results since
					//   outside factors could affect this
					//   calculation
			
		tries++;		// Increment number of times sampled
						//   on this call to cpuspeed
			                        
		freq3 = freq2;	// Shift frequencies back to make
		freq2 = freq;	//   room for new frequency 
							//   measurement

   		t0 = timeGetTime();
    		
		t1 = t0;		// Set Initial Time

   		while ( t1 - t0 < INITIAL_DELAY ) {
   						// Loop until three ticks have 
   						//   passed	since last read of 
						//	 timeGetTime. This accounts for
						//   overhead later.

			t1 = timeGetTime();
		}					

   		__asm						// Read Time Stamp...
		{                       
			RDTSC
			    
			MOV CL, 16
							
			MOV u0, AX
			OPND32
			SHR	AX,CL
			MOV u1, AX
        }                   
		
		t0 = t1;					// Reset Initial Time
			
  		while ( t1 - t0 < SAMPLING_DELAY ) {
   					  	// Loop until 60 ticks have passed 
   					  	//   since last timeGetTime read. 
   					  	//   This allows for elapsed time
   					  	//   for sampling
    					  	
			t1 = timeGetTime();
		}							
			

   	    __asm						// Read Time Stamp...
		{
			RDTSC
				
			MOV CL, 16
							
			MOV v0, AX
			OPND32
			SHR	AX,CL
			MOV v1, AX
        }                   
		
		stamp0 = (ulong) u1*65536 + u0;
		stamp1 = (ulong) v1*65536 + v0;
						// Move two 16-bit values into one 
						//   32-bit value for the time stamp
						//   read at both the beginning and 
						//   end of the test.
   												
       	cycles = stamp1 - stamp0;	// Number of internal 
       								//   clock cycles is 
       								//   difference between 
       								//   two time stamp 
       								//   readings.

   		ticks = (ulong) t1 - t0;	// Number of external 
   									//   ticks is difference 
   									//   between two 
   									//   timeGetTime reads
		                            
        ticks = ticks * 1000;		// Convert ticks to us 
           							//   (since the 
           							//   timeGetTime
           							//   frequency is 1 
           							//   tick/ms).

		total_ticks += ticks;
		total_cycles += cycles;

		freq = cycles/ticks;		// Cycles / us  = MHz
        										
      	if ( cycles%ticks > ticks/2 )
       		freq++;					// Round up if necessary	
          		
		total = ( freq + freq2 + freq3 );
							// Total last three frequency 
							//   calculations

				
	} while((tries<3) || 			
	        (tries<MAX_TRIES)&&
	        ((abs(3*(int)freq -(int)total)>3*TOLERANCE)||
	         (abs(3*(int)freq2-(int)total)>3*TOLERANCE)||
	         (abs(3*(int)freq3-(int)total)>3*TOLERANCE)));	
					// Compare last three calculations to 
	          		//   average of last three calculations.		
		
	// Try one more significant digit.
	freq3 = ( total_cycles * 10 ) / total_ticks;
	freq2 = ( total_cycles * 100 ) / total_ticks;

	if ( freq2 - (freq3 * 10) >= ROUND_THRESHOLD )
		freq3++;

	cpu_speed.raw_freq = total_cycles / total_ticks;
	cpu_speed.norm_freq = cpu_speed.raw_freq;

	freq = cpu_speed.raw_freq * 10;
	if( (freq3 - freq) >= ROUND_THRESHOLD )
		cpu_speed.norm_freq++;

	cpu_speed.ex_ticks = total_ticks;
	cpu_speed.in_cycles = total_cycles;

	return cpu_speed;
}    


static int GetCmosTick(void)
{
	int tick = 0;

	// __asm	mov ah, 02h
	// __asm	int 1Ah
	// __asm	mov al, dh
	// __asm	and ax, 000Fh  

	__asm  xor ax, ax
	__asm  out 070h, al

	__asm  xor ax, ax
	__asm  in  al, 071h

    // _outp( 0x70, offset );
    // base = _inp( 0x71 ); 

// value returned in ax by function

	__asm 	mov word ptr tick, ax

	return tick;
}


//#define ABS_TICK(a,b)  (b<a)?b+60-a:b-a
// since I am only interested in single ticks
#define ABS_TICK(a,b)  (b<a)?b+10-a:b-a

static struct FREQ_INFO GetCmosCpuSpeed()
{
	int	timeStart, timeStop, lapseTime;
	unsigned long   temp;
	unsigned long   temp1;
	struct FREQ_INFO cpu_speed;
	unsigned long   cpuSpeed = 0l;
	ulong  stamp0, stamp1;			// Time Stamp Variable 
									//   for beginning and end 
    
    ushort u0,u1;     		        // 16-bit variables for time
    ushort v0,v1;					//   stamp reads. These are 
    								//   later merged into 
    								//   stamp0, and stamp1 
    								//   (32-bit variables)

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));

	// This loop waits for the next tick
	// so that we begin speed test on a tick edge
	timeStart = GetCmosTick();
	for(;;)
	{
		timeStop = GetCmosTick();
		if (  ABS_TICK(timeStart,timeStop) > 0 )
		{
			__asm						// Read Time Stamp...
			{                       
				RDTSC
			    
				MOV CL, 16
							
				MOV u0, AX
				OPND32
				SHR	AX,CL
				MOV u1, AX
			}                   
			break;	
		}	
	}

	timeStart = timeStop;

	for(;;)
	{
		timeStop = GetCmosTick();
		if (  ABS_TICK(timeStart,timeStop) > 0 )
		{
			__asm						// Read Time Stamp...
			{
				RDTSC
				
				MOV CL, 16
							
				MOV v0, AX
				OPND32
				SHR	AX,CL
				MOV v1, AX
	        }                   
			break;	
		}	
	}

	// convert into long values
	stamp0 = (ulong) u1*65536 + u0;
	stamp1 = (ulong) v1*65536 + v0;

	lapseTime = ABS_TICK(timeStart,timeStop);

	cpuSpeed = stamp1 - stamp0; ///lapseTime; 
	cpu_speed.in_cycles = cpuSpeed;		// Cycles count since we in this routine

	//round to nearest digit
	temp =  cpuSpeed/1000000; 	
	temp1 = cpuSpeed/100000;  
	temp = temp * 10;  // realign with last digit = zero

	cpuSpeed = cpuSpeed/1000000; // cpuSpeed/1000000;
	cpu_speed.raw_freq = cpuSpeed;	

	if( (temp1 - temp) >= ROUND_THRESHOLD )
		cpuSpeed++;
	
	cpu_speed.norm_freq = cpuSpeed;	
	cpu_speed.ex_ticks = (timeStop - timeStart) * 1000000;

	return cpu_speed;			
}
