; ****************************************************************
; * Program:"Cmos self rewrite MBR" install program cbootld.asm  *
; *==============================================================*
; * tasm cbootld.asm                                             *
; * tlink /t cbootld.asm                                         *
; *==============================================================*
; * Designer:Howard                                              *
; * Creat Date:09/14/1999                                        *
; * Original Place:Wuhan                                         *
; * Modification Date:09/14/1999                                 *
; * Now Version: 1.0                                             *
; *--------------------------------------------------------------*
; *                Modification History                          *
; *--------------------------------------------------------------*
; * Version 1.0  1.Install the cmos self_rewrite MBR to Harddisk,*
; * 09/14/1999     Cylinder 00h,head 00h,sector 01h.             *
; *              2.Backup the old MBR to the Harddisk,saved      *
; *                the backup data to the O track No.3,5 sector. *
; ****************************************************************


 CmosselfcheckedMbr_load segment
	 org 100h
	 assume cs:CmosselfcheckedMbr_load

 Start:
 main proc near
	 push cs
	 pop  ds
	 push cs
	 pop  es
	 mov  ax,0201h
	 lea  bx,buffer
	 mov  cx,0001h
	 mov  dx,0080h
	 int  13h
	 jnb  hdreadok
	 jb   hdreaderr
 hdreaderr:
	 mov  dx,offset hdreaderrmsg
	 call disp
	 call exit
 hdreadok:
	 ;lea  dx,hdreadok
	 ;call disp
 movepartitiontable:
	 cld
	 mov  si,offset buffer+01beh
	 mov  di,offset sector+01beh
	 mov  cx,0040h
	 repne movsb

 bakmbr:
	 mov  ax,0301h
	 mov  cx,000ch
	 mov  dx,0080h
	 int  13h
	 jnb  hdwriteok
	 jb   hdwriteerr

 hdwriteerr:
	 lea  dx,hdwriteerrmsg
	 call disp
	 call exit

 hdwriteok:
	 mov  ax,0301h
	 mov  cx,001eh
	 mov  dx,0080h
	 int  13h
	 jb   hdwriteerr

	 mov  ax,0301h
	 mov  bx,offset Sector
	 mov  cx,0001h
	 mov  dx,0080h
	 int  13h
	 jnb  mbrwriteok
	 jb   hdwriteerr

 mbrwriteok:
	 mov  dx,offset mbrwriteokmsg
	 call disp
	 call exit
 main endp
 disp proc near
	 mov  ah,09h
	 int  21h
 disp endp
 exit proc near
	 mov  ah,4ch
	 int  21h
 exit endp

 sector db  0FAh,33h,0C0h,8Eh,0D0h,0BCh,00h,7Ch,8Bh,0F4h,50h,07h
	db  50h,1Fh,0FBh,0FCh,0BFh,00h,06h,0B9h,00h,01h,0F2h,0A5h
	db  0EAh,1Dh,06h,00h,00h,0B8h,01h,02h,0BBh,00h,08h,0B9h
	db  1Dh,00h,0BAh,80h,00h,0CDh,13h,0B8h,10h,00h,0B9h,70h
	db  00h,0FCh,0E6h,70h,50h,8Ah,07h,0E6h,71h,58h,0FEh,0C0h
	db  43h,0E2h,0F3h,0FDh,0BEh,0BEh,07h,0B3h,04h,80h,3Ch,80h
	db  74h,0Eh,80h,3Ch,00h,75h,1Ch,83h,0C6h,10h,0FEh,0CBh
	db  75h,0EFh,0CDh,18h,8Bh,14h,8Bh,4Ch,02h,8Bh,0EEh,83h
	db  0C6h,10h,0FEh,0CBh,74h,0Dh,80h,3Ch,00h,74h,0F4h,0BEh
	db  0A1h,06h,0E8h,83h,00h,0EBh,0FEh,0BFh,05h,00h,0BBh,00h
	db  7Ch,0B8h,01h,02h,57h,0CDh,13h,5Fh,73h,0Ch,33h,0C0h
	db  0CDh,13h,4Fh,75h,0EDh,0BEh,0BAh,06h,0EBh,0E0h,0BEh,0DAh
	db  06h,0BFh,0FEh,7Dh,81h,3Dh,55h,0AAh,75h,0D4h,8Bh,0F5h
	db  0EAh,00h,7Ch,00h,00h,49h,6Eh,76h,61h,6Ch,69h,64h
	db  20h,70h,61h,72h,74h,69h,74h,69h,6Fh,6Eh,20h,74h
	db  61h,62h,6Ch,65h,2Eh,00h,45h,72h,72h,6Fh,72h,20h
	db  6Ch,6Fh,61h,64h,69h,6Eh,67h,20h,6Fh,70h,65h,72h
	db  61h,74h,69h,6Eh,67h,20h,73h,79h,73h,74h,65h,6Dh
	db  2Eh,00h,4Dh,69h,73h,73h,69h,6Eh,67h,20h,6Fh,70h
	db  65h,72h,61h,74h,69h,6Eh,67h,20h,73h,79h,73h,74h
	db  65h,6Dh,2Eh,00h,0ACh,3Ch,00h,74h,0Bh,56h,0BBh,07h
	db  00h,0B4h,0Eh,0CDh,10h,5Eh,0EBh,0F0h,0C3h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,80h,01h,01h,00h,06h,3Fh,7Fh,96h,3Fh,00h
	db  00h,00h,01h,0Ah,19h,00h,00h,00h,41h,97h,0Fh,3Fh
	db  0FFh,0FDh,40h,0Ah,19h,00h,00h,0E6h,25h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,55h,0AAh
 buffer db 512 dup(0)
 hdreaderrmsg db 0dh,0ah,'Hard Disk Sector Reading Error...','$'
 hdreadokmsg  db 0dh,0ah,'Hard Disk Sector Reading OK...','$'
 hdwriteerrmsg db 0dh,0ah,'Hard Disk Sector Writing Error...','$'
 hdwriteokmsg  db 0dh,0ah,'Hard Disk Sector Writing OK...','$'
 mbrwriteokmsg db 0dh,0ah,'MBR Writing OK...','$'

 CmosselfcheckedMbr_load ends
    end start