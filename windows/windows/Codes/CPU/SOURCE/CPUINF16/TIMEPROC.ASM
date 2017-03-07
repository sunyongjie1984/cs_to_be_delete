;***************************************************************
; MASM file: timeproc.asm... for cpuinf16 DLL
;
;       This program has been developed by Intel Corporation.  
;		You have Intel's permission to incorporate this code 
;       into your product, royalty free.  Intel has various 
;	    intellectual property rights which it may assert under
;       certain circumstances, such as if another manufacturer's
;       processor mis-identifies itself as being "GenuineIntel"
;		when the CPUID instruction is executed.
;
;       Intel specifically disclaims all warranties, express or
;       implied, and all liability, including consequential and
;		other indirect damages, for the use of this code, 
;		including liability for infringement of any proprietary
;		rights, and including the warranties of merchantability
;		and fitness for a particular purpose.  Intel does not 
;		assume any responsibility for any errors which may 
;		appear in this code nor any responsibility to update it.
;
;****************************************************************



ITERATIONS equ 4000

.8086
.model medium,c
.code


.386

			; Declare functions to be public and therefore accessible by C programs.
public Time_Processor_bsf



;***************************************************************
; TIME_PROCESSOR_BSF() -- Perform nITERATIONS of the BSF 
;                         instructions.
;
; Inputs: none
;
; Returns:
;	# of ticks instruction sequence ran.
;***************************************************************

Time_Processor_bsf proc	far

;---------- Initialize and Clear Timer -------------------------

			mov al,10111000b	; Channel 2, LSB+MSB, mode 4,
			out 43h,al          ;    binary

			in	al,61h
			or	al,1
			out 61h,al

			xor al,al           ; Reset timer
			out 42h,al
			out 42h,al
                            
                            
;---------- Run nIterations of the BSF Instruction -------------

		mov eax,80000000h
		mov bx,ITERATIONS
	
loop1:	bsf ecx,eax
        
        dec	bx
		jnz	loop1
                            
                            
;---------- Read Timer Ticks -----------------------------------

		in	al,42h				; MSB timer
		mov	ah,al
		in	al,42h				; LSB timer
		xchg	al,ah
		neg	ax

	 	retf					; Set return type to be far

Time_Processor_bsf endp

end
