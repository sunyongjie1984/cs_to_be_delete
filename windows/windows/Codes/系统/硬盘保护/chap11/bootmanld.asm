;bootmanld.asm     ---bootm.asm install program
;masm   bootmanld
;link   bootmanld
;exe2com  bootmanld
;Usage: Before running this program,you must place a floppy in drive a:,
;       and run this program,choose the disk type.Just for 1.2M floppy.
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;page:182
;creat on 02/21/1999

           .model tiny
	   .code
	   org   100h
start:
       jmp   begin
      
track   equ  50h
head    equ  00h

buffer    db  512  dup (0)

sector  db  0EBh,29h,90h,48h,6Fh,77h,61h,72h,64h,20h,00h,02h
	db  01h,01h,00h,02h,0E0h,00h,40h,0Bh,0F0h,09h,00h,12h
	db  00h,02h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,0FAh,33h,0C0h,8Eh,0D0h
	db  0BCh,00h,7Ch,8Bh,0F4h,50h,07h,50h,1Fh,0FCh,0BFh,00h
	db  06h,0B9h,00h,01h,0F2h,0A5h,33h,0C0h,50h,0B8h,4Ah,06h
	db  50h,0CBh,0BFh,7Ch,06h,0E8h,9Bh,01h,0B4h,00h,0CDh,16h
	db  24h,5Fh,3Ch,41h,74h,06h,3Ch,43h,74h,0Bh,0EBh,0F0h
	db  0B9h,01h,50h,0BAh,00h,00h,0EBh,07h,90h,0B9h,01h,00h
	db  0BAh,80h,00h,0B8h,01h,02h,0BBh,00h,7Ch,0CDh,13h,0EAh
	db  00h,7Ch,00h,00h,20h,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,0Dh,0Ah,7Ch,20h,20h
	db  20h,20h,2Ah,2Ah,2Ah,20h,48h,61h,72h,64h,64h,69h
	db  73h,6Bh,20h,62h,6Fh,6Fh,74h,65h,72h,20h,66h,6Ch
	db  6Fh,70h,70h,79h,20h,2Ah,2Ah,2Ah,20h,20h,20h,20h
	db  7Ch,0Dh,0Ah,7Ch,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh
	db  3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh
	db  3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh
	db  3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,7Ch,0Dh,0Ah,7Ch,20h,20h
	db  20h,20h,20h,20h,20h,20h,20h,20h,20h,56h,65h,72h
	db  73h,69h,6Fh,6Eh,20h,31h,2Eh,30h,30h,20h,20h,20h
	db  20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h
	db  7Ch,0Dh,0Ah,7Ch,20h,20h,20h,20h,54h,68h,69h,73h
	db  20h,64h,69h,73h,6Bh,65h,74h,74h,65h,20h,69h,73h
	db  20h,66h,6Fh,72h,63h,65h,64h,20h,74h,6Fh,20h,62h
	db  6Fh,6Fh,74h,20h,20h,20h,7Ch,0Dh,0Ah,7Ch,20h,20h
	db  20h,20h,66h,72h,6Fh,6Dh,20h,74h,68h,65h,20h,48h
	db  61h,72h,64h,20h,44h,69h,73h,6Bh,2Eh,2Eh,2Eh,20h
	db  20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h
	db  7Ch,0Dh,0Ah,7Ch,20h,20h,20h,20h,20h,20h,20h,20h
	db  20h,20h,20h,20h,20h,20h,62h,79h,20h,48h,6Fh,77h
	db  61h,72h,64h,2Ch,20h,30h,32h,2Fh,32h,31h,2Fh,31h
	db  39h,39h,39h,20h,20h,20h,7Ch,0Dh,0Ah,7Ch,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  7Ch,0Dh,0Ah,20h,42h,6Fh,6Fh,74h,20h,66h,72h,6Fh
	db  6Dh,20h,64h,72h,69h,76h,65h,20h,28h,41h,29h,2Ch
	db  64h,72h,69h,76h,65h,20h,28h,43h,29h,3Ah,24h,2Eh
	db  8Ah,05h,3Ch,24h,74h,0Ah,0B4h,0Eh,0BBh,03h,00h,0CDh
	db  10h,47h,0EBh,0EFh,0C3h,00h,55h,0AAh


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
       mov   di,5
       push  cs
       pop   ds
       push  cs
       pop   es
rdboot:
       mov   dx,00h
       int   13h
       mov   ax,0201h
       mov   bx,offset buffer
       mov   cx,0001h
       mov   dx,0
       int   13h
       jnc   readok
       dec   di
       jnz   rdboot

readok:
       mov   di,5

wrtboot:
       mov   dx,00h
       int   13h

       mov   ax,0301h
       mov   bx,offset sector
       mov   cx,0001h
       mov   dx,0h
       int   13h
       jc    wrtboot
       mov   ax,0301h
       mov   bx,offset buffer
       mov   cx,5001h
       mov   dx,0
       int   13h
       jnc   writeok
       dec   di
       jnz   wrtboot

writeok:
       mov   ah,4ch
       int   21h
      end   start
      