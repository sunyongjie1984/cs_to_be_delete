ReadMe16.txt----------------------------------------------------

                  16-bit DLL and Test Program

Contents:
    
    o EXECUTE\CPUINF16.DLL    -- 16-bit CPUINFO DLL
    o EXECUTE\TSTDLL16.EXE    -- Test Program for CPUINF16.DLL
    o SOURCE\*.*              -- Source Files for the DLLs, the
                                   test programs, and the DOS
                                   code

Installation:

 Copy both the TSTDLL16.EXE file and the CPUINF16.DLL file to
 the same directory. Execute the TSTDLL16.EXE program.

 The DLL does not have to be placed in the same directory, but
 if it is not placed in the same directory that the program
 is executed from, the DLL must be pointed to by the PATH.
 Otherwise the Windows* will not know where to find the file.


OVERVIEW

 TSTDLL16 is a 16-bit MS-Windows* test program for the CPUINF16
 DLL. TSTDLL16 requires at least an Intel386(TM) processor and
 MS-Windows 3.1. The CPUINF16 DLL contains functions to return
 the family, type/family/model/stepping, feature flags,
 processor speed, and time stamp reading of the host processor.
 Note that some functions do not pertain to all systems. See
 below for further information.
 
 To determine what type of processor is in the computer, 
 the CPUINF16 DLL uses the standard Intel cpuid assembly code.
 To determine clock speed, the CPUINF16 DLL uses one of two 
 algorithms. 

 The first algorithm (for use on systems not supporting the 
 Time Stamp Register) directly uses the PC Chipset Timer to 
 determine the amount of time taken to run a specified set of
 instructions. The speed is then calculated based on the number
 of cycles run and the number of microseconds it took to run 
 them. This algorithm is basically a very crude benchmark test.
 
 The second algorithm (for use on systems which do support the
 Time Stamp Register) utilizes the Windows API call 
 timeGetTime() in place of directly reading the PC Chipset 
 Timer. Instead of using a set number of instructions to 
 determine the number of cycles executed throughout the test, 
 this algorithm simply reads the Time Stamp at the beginning 
 and the end of the test to find how many cycles have passed.


Test Program Functionality

 1. CPU Family - this tests the wincpuid() function in 
      CPUINF16.DLL, and returns the cpu Family (5-Pentium(R)
      processor, 4-i486(TM) processor ...) as a hex number in a
      windows message box.

 2. CPU Extensions - this tests the wincpuidext() function in 
      CPUINF16.DLL, and returns the Processor Type/Family/
      Model/Stepping as a hexidecimal number in a windows 
      message box. The processor T/F/M/S are a 16-bit quantity
      returned in the AX register by the CPUID operation.  If 
      CPUID is not supported, only the Family, in bits 11:8,
      are displayed by TSTDLL16.
         AX(15:14) = Reserved
         AX(13:12) = Processor type
         AX(11:8)  = CPU Family
         AX(7:4)   = CPU Model(if CPUID supported)
         AX(3:0)   = Stepping #(if CPUID supported)

 3. CPU Speed - this tests the cpuspeed() function in
      CPUINF16.DLL, and returns a FREQ_INFO structure which
      contains the calculated speed of the processor, the
      normalized (to the nearest known processor speed) value
      of the processor, and the number of clock cycles and
      microseconds that elapsed during the test sampling. After
      displaying this information, the user is asked whether
      to proceed with the testing and run 100 more iterations
      of the test. The results are then displayed
      statistically. This statistical feedback is primarily for
      the user to get information on the precision of the 
      cpuspeed() function. Note- Multiple sampling iterations
      is done within cpuspeed() as well. In most cases, 
      multiple calls to cpuspeed will not increase the
      accuracy of the data.If greater accuracy is necessary
      simply adjust the constants in SPEED.H.

 4. CPU Features - this tests the wincpufeatures() function in 
      cpuid16.DLL, and returns the Feature Flags as a 
      hexidecimal number in a windows message box. The Feature
      Flags are a 32-bit quantity returned in the EDX register
      by the CPUID operation.

 5. Read Time Stamp - this tests the winrdtsc() function in
      CPUINF16.DLL. The 64-bit Time Stamp register is currently
      available only on Pentium(R) and Pentium Pro(R)
      processors. All other processors will return all zeroes
      for the time stamp value.

6. Get DLL Version - this tests the getdllversion() function in
      CPUINF16.DLL. It returns an unsigned short. The upper byte
      is the major version and the lower byte is the minor 
      version.



    +----------------------------------------------------------+
    | This program has been developed by Intel Corporation.    |
    | You have Intel's permission to incorporate this code     |
    | into your product, royalty free.  Intel has various      |
    | intellectual property rights which it may assert under   |
    | certain circumstances, such as if another manufacturer's |
    | processor mis-identifies itself as being "GenuineIntel"  |
    | when the CPUID instruction is executed.                  |
    |                                                          |
    | Intel specifically disclaims all warranties, express or  |
    | implied, and all liability, including consequential and  |
    | other indirect damages, for the use of this code,        |
    | including liability for infringement of any proprietary  |
    | rights, and including the warranties of merchantability  |
    | and fitness for a particular purpose.  Intel does not    |
    | assume any responsibility for any errors which may       |
    | appear in this code nor any responsibility to update it. |
    +----------------------------------------------------------+

  Information in this document is provided in connection with
  Intel products.  Intel assumes no liability whatsoever, 
  including infringement of any patent or copyright, for sale 
  and use of Intel products except as provided in Intel's Terms 
  and Conditions of Sale for such products.
     
  Intel retains the right to make changes to these specifications 
  at any time, without notice.
  

  * Other brands and names are the property of their respective
    owners.
  
  Copyright (c) 1995, Intel Corporation.  All rights reserved.

----------------------------------------------------ReadMe16.txt
