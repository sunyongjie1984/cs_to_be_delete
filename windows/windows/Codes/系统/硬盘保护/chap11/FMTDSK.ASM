;program name: FMTDSK.asm
;Usage: 

;masm fmtdsk
;link fmtdsk
;exe2bin fmtdsk
;tasm fmtdsk
;tlink /t fmtdsk
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;PAGE: 177
;CREAT ON 02/21/1999
;just for drive B and 1.2M floppy
;modify the program for A drive and 1.44M floppy

        .MODEL TINY
	.CODE
	ORG    100H

	
start:
       jmp   begin
track        equ   50h
head         equ   00h
;1.2M floppy fmttable ,you can add the data for 1.44m floppy
fmtable  db track,head,0a1h,02,track,head,0b1h,02h,track,head,0c1h,02h
         db track,head,0d1h,02,track,head,0e1h,02h,track,head,0f1h,02h
	 db track,head,0a2h,02,track,head,0b2h,02h,track,head,0c2h,02h
	 db track,head,0abh,02,track,head,0bbh,02h,track,head,0cch,02h
	 db track,head,0ddh,02,track,head,0eeh,02h,track,head,0ffh,02h

begin:
       push  cs
       pop   ds
       mov   ax,351eh
       int   21h
       mov   byte ptr es:[bx+3],2
       mov   byte ptr es:[bx+4],0fh
       mov   byte ptr es:[bx+5],2ah
       mov   byte ptr es:[bx+7],50h
       mov   byte ptr es:[bx+8],0ach
       push  cs
       pop   es
       mov   di,5
       
fmt:
       mov   ax,0
       mov   dx,01
       int   13h
       mov   ax,050fh
       mov   ch,50h
       mov   dx,01h
       mov   bx,offset fmtable
       int   13h
       jnc   fmtok
       dec   di
       jnz   fmt

fmtok:
       mov   ah,4ch
       int   21h
       end start
       
       