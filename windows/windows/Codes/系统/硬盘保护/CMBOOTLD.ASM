; *********************************************************************
; * Program:The Cmboot.exe MBR Sector loader.And read the cmos data   *
; *         and saved it to the harddisk hidden sector.               * 
; *===================================================================*
; * tasm Cmbootld1.asm                                                *
; * tlink Cmbootld                                                    *
; *===================================================================*
; * Designer:Howard                                                   *
; * Creat Date:09/29/1999                                             *
; * Original place:Wuhan                                              *
; * Modification date:09/29/1999                                      *
; * Now Version:1.0                                                   *
; *===================================================================*
; *                Modification History                               *
; *-------------------------------------------------------------------*
; * Version:1.0   1.Backup the old mbr to a file.                     *
; * 09/29/1999    2.Load the backup mbr file and saved it to the mbr  *
; *                 sector(cylinder:0,head:0,sector:1).               *
; *               3.Saved the cmos data to hard disk hidden sector.   *
; *               4.Load the cmoscheckedmbr the mbr sector.           *
; *               5.Reboot the computer.                              *
; *-------------------------------------------------------------------*
; * 09/30/1999    6.Modify the psp and _data segment mistake.         *
; *-------------------------------------------------------------------*
; * 10/01/1999    7.Modify some bug,and optimize some instructions.   *
; *-------------------------------------------------------------------*
; * 10/07/1999    8.Modify the parameter error,ignore the space bet-  *
; *                 ween the program name and parameter.              *
; *               9.Modify the file creating problem,add zero to the  *
; *                 end of filename string.                           *
; *********************************************************************
; * problem: 1.The _data and psp segment address is still a problem.  *
; * 10/01/99   Use a debug information.Maybe the buffer offset address*
; *            is not correct,or the data segment is too large.       *
; *            I haved used two mem unit to save the psp and _data    *
; *            segment address.Do not use the stack to save psp and   *
; *            data segment address.                                  *
; *          2.The file "creat/open/read/write" operating is still    *
; *            a problem.                                             *
; *-------------------------------------------------------------------*
; * bugs:      1.Int 13h ah=02/03h es:bx point to the buffer,but      *
; * modifying    program executing,es=psp segment address,it must     *
; * 10/01/99     be make it equarl the real buffer segment address.   *
; *            2.Push and pop operating must be make sure the         * 
; *              operands is correct.                                 *
; * 10/07/99   3.The program can not creat a new file.error writing   *
; *              device AUX.                                          *              
; *********************************************************************

;      dosseg
      .model small
      .486
      .stack  200h 
      .data

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
       
       res    dw 0072h,0040h
       dat    dw 0000h,0ffffh
       buffer db 512 dup(0)
       filename db 'hdpt.dat',0
       parameter db 2 dup(?)
       copyright db 0dh,0ah,'JiangBiFang,I love you!','$'
       helpmsg db 0dh,0ah,'1.cmbootld /c'
               db 0dh,0ah,'  Saved the cmos data to hard disk hidden sector.'
	       db 0dh,0ah,'2.cmbootld /w'
	       db 0dh,0ah,'  Load the old mbr data from a file and saved it to mbr sector.'
               db 0dh,0ah,'3.cmbootld /s'
	       db 0dh,0ah,'  Saved the mbr sector to a file.'
	       db 0dh,0ah,'4.cmbootld /l'
	       db 0dh,0ah,'  Load the cmoschecked mbr sector to hard disk.'
	       db 0dh,0ah,'5.cmbootld /r'
	       db 0dh,0ah,'  Reboot the computer.'
	       db 0dh,0ah,'6.cmbootld /?'
	       db 0dh,0ah,'  Print the help message.','$'
       noparamsg db 0dh,0ah,'Please use cmbootld /? for help.','$'	            
;       debug     db 0dh,0ah,'Debug message.','$'
       hdbkokmsg db 0dh,0ah,'Harddisk mbr back ok.','$'
       hdreaderrmsg db 0dh,0ah,'Harddisk reading error!','$'
       hdwriteerrmsg db 0dh,0ah,'Harddisk writing error!','$'
       filecreaterrmsg db 0dh,0ah,'File creating error!','$'
       fileopenerrmsg db 0dh,0ah,'File opening error!','$'
       filewriteerrmsg db 0dh,0ah,'File writing error!','$'
       filewriteokmsg  db 0dh,0ah,'File writing OK!','$'
       filereaderrmsg  db 0dh,0ah,'File reading error!','$'
       mbrwriteokmsg   db 0dh,0ah,'The cmoschecked mbr loading ok!','$'
       cmossavedtohdokmsg db 0dh,0ah,'The cmos data haved to harddisk.','$'
       mbrbkokmsg  db 0dh,0ah,'The old mbr haved backup to the file hdpt.dat.','$'
       cmoscheckedmbrldokmsg db 0dh,0ah,'The cmoscheckedmbr haved installed ok!','$'
       wrongparamsg db 0dh,0ah,'The wrong parameter:"','$'       
       .code
start:       
main proc far
          assume cs:_text,ds:_data,es:_data,ss:stack
         mov  cs:pspseg,ds
;         push ds
	 xor  ax,ax
	 mov  ax,_data
	 mov  cs:dataseg1,ax
	 mov  ds,ax           ;ds=_data 
	 
	 mov  es,ax           ;int 13h es:bx point to buffer,es=seg _data
	 lea  dx,copyright
	 call disp1	 
;        push ds
;	 pop  cx              ;cx=_data
;        pop  ds	      ;ds=psg
	 mov  ds,cs:pspseg              ;ds=psp 
	 cld
	 mov  si,81h
	 lodsb
;	 push ds
;        mov  ds,cx                     ;ds=_data seg
	 mov  ds,cs:dataseg1            ;ds=_data
	 cmp  al,0dh
         jz   nopara
	 cmp  al,' '
	 jz   judgespace
;         pop  ds                ;ds=psp
continue:	 
         push si
	 dec  si
         mov  ds,cs:pspseg
	 lodsb
;	 push ds
;        mov  ds,cx                       ;ds=_data 
	 mov  ds,cs:dataseg1              ;ds=_data
         lea  bx,parameter
	 cmp  al,'/'
	 jz   scanparaloop
	; lea  bx,parameter
;        push ds	
         jmp  error


scanparaloop:
         mov  [bx],al
;	 pop  ds                  ;ds=psp
         mov  ds,cs:pspseg
	 lodsb
;	 push ds
;        mov  ds,cx                        ;ds=_data
	 mov  ds,cs:dataseg1               ;ds=_data
	 cmp  al,0dh
	 jz   choise
	 inc  bx
	 jnb  scanparaloop        ;instruction loop can not use rigister cx,
	 
judgespace:
         mov  ds,cs:pspseg
         lodsb
;        call debug         ;set break point	 
	 cmp  al,0dh
	 je   nopara
	 cmp  al,' '
	 je   judgespace
	 jne  continue	 	 
nopara:
         lea  dx,noparamsg
	 jmp  disp
;         call disp
;         call rettodos

help:
         lea  dx,helpmsg
	 jmp  disp
;	 call disp
;	 call rettodos

choise:
;         push cx
;         mov  ds,dataseg1
         lea  si,parameter
	 mov  al,[si+1]
	 cmp  al,'s'
	 jz   savembr
	 cmp  al,'S'
	 jz   savembr
	 cmp  al,'w'
	 jz   writembr
	 cmp  al,'W'
	 jz   writembr
	 cmp  al,'c'
	 jz   savedcmosdatatohd
	 cmp  al,'C'
	 jz   savedcmosdatatohd
	 cmp  al,'r'
	 jz   reboot
	 cmp  al,'R'
	 jz   reboot
	 cmp  al,'l'
	 jz   cmoscheckedmbrld
	 cmp  al,'L'
	 jz   cmoscheckedmbrld
	 cmp  al,'?'
	 jz   help
	 jmp  error

savembr:
;    -----  Debug instrution ------
;         mov  ds,cs:dataseg1
;         lea  dx,debug
;	 call disp1
;	 mov  ah,07h
;	 int  21h
;	 cli
;    ------------------------------	
;         sub  ax,ax
;        pop  ds             ;ds=_data
;        push ds
;        pop  es             ;es=_data
         mov  ax,0201h
;	 mov  bx,offset buffer
         lea  bx,buffer	     ;es:bx=_data:buffer ,es=seg _data
	 mov  cx,0001h
	 mov  dx,0080h
	 int  13h	     
;	 push bx
	 jb   harddiskreaderr
;	 mov  ax,_data
;	 mov  ds,ax
;	 push bx 	
         xor  bx,bx
	 mov  dx,offset filename
	 mov  cx,0
	 mov  ah,3ch
	 int  21h
	 jc   filecreaterr 
	 mov  bx,ax
	 mov  dx,offset buffer
;	 pop  dx
         mov  cx,200h
	 mov  ah,40h
	 int  21h
	 jc   filewriteerr
	 mov  ah,3eh
	 int  21h
	 jmp  filewriteok 
	
filecreaterr:
         lea  dx,filecreaterrmsg
	 jmp  disp
;	 call disp
;	 call rettodos
filewriteerr:
         lea  dx,filewriteerrmsg
;	 call disp
;	 call rettodos
         jmp  disp
harddiskreaderr:
         lea  dx,hdreaderrmsg
	 jmp  disp
	 
;	 call disp
;	 call rettodos
filewriteok:
         lea  dx,filewriteokmsg
	 jmp  disp
;	 call disp
;	 call rettodos

writembr:
;        pop  ds	   ;ds=_data
;        push ds	   
;        pop  es	   ;es=_data
         lea  dx,filename
	 mov  ax,3d00h
	 mov  cx,0
	 int  21h
	 jc   fileopenerr
	 mov  bx,ax
	 mov  cx,200h
	 lea  dx,buffer
	 push dx
	 mov  ah,3fh
	 int  21h
	 jc   filereaderr
	 mov  ah,3eh
	 int  21h
	 pop  bx
	 mov  ax,0301h
	 mov  cx,0001h
	 mov  dx,0080h
	 int  13h
	 jb   hdwriteerr
	 jnb  mbrwriteok
;	 jmp  reboot
filereaderr:
         lea  dx,filereaderrmsg
	 jmp  disp
;	 call disp
;	 call rettodos
fileopenerr:
         lea  dx,fileopenerrmsg
	 jmp  disp
;	 call disp
;	 call rettodos
hdwriteerr:
         lea  dx,hdwriteerrmsg
	 jmp  disp
;	 call disp
;	 call rettodos
hdreaderr:
         lea  dx,hdreaderrmsg
	 jmp  disp
;	 call disp
;	 call rettodos
mbrwriteok:
         lea  dx,mbrwriteokmsg
	 call disp1
;	 jmp  reboot
	 call rettodos
savedcmosdatatohd:
;         mov  ds,cs:[dataseg1]       ;pop ds    ;ds=_data seg
;	 push ds
;	 pop  es		    ;es=_data
         mov  bx,offset buffer
	 cld
	 xor  cx,cx
	 push cx
	 pop  ax
	 mov  cx,70h
	 mov  al,10h
	 push bx              ;mistake goes here,it must be push
	 cld
cmosdatareadloop:
         out  70h,al
	 push ax
	 in   al,71h
	 mov  ds:[bx],al
	 pop  ax
	 inc  bx
	 inc  al
	 loop cmosdatareadloop
	 std
	 pop  bx	     ;lea bx,buffer
	 mov  ax,0301h
;	 mov  bx,offset buffer
         mov  cx,1ch         ;modify the number
	 mov  dx,0080h
	 int  13h
	 jb   hdwriteerr
;	 jb   cmossavetohdok

cmossavetohdok:
         lea  dx,cmossavedtohdokmsg
	 jmp  disp
;	 call disp
;	 call rettodos

cmoscheckedmbrld:
         mov  ax,0201h
	 mov  bx,offset buffer
	 mov  cx,0001h
	 mov  dx,0080h
	 int  13h
	 jb   hdreaderr
	 cld
	 mov  si,offset buffer+01beh
	 mov  di,offset sector+01beh
	 mov  cx,40h
	 repne movsb
;	 std
	 mov  ax,0301h
	 mov  bx,offset buffer
	 mov  cx,19
	 mov  dx,0080h
	 int  13h
	 jb   hdwriteerr
	 lea  dx,mbrbkokmsg
	 call disp1
	 mov  ax,0301h
	 mov  bx,offset sector
	 mov  cx,0001h
	 mov  dx,0080h
	 int  13h	  
	 jb   hdwriteerr
	 lea  dx,cmoscheckedmbrldokmsg
	 call disp1
;	 jmp  reboot
	 jmp  rettodos
error:
;        pop  ds               ;ds=_data 
         lea  dx,wrongparamsg
	 call disp1
	 mov  ax,0200h
;         mov  si,81h
;	 inc  si
;         pop  ds           ;ds=psp
         mov  ds,cs:pspseg
;         mov  si,81h
         pop  si
	 dec  si
prnwrongparameter:
;        mov  dl,ds:[si]
;        cmp  dl,0dh
;        jz   retdos
;        mov  ah,02h
;        int  21h
;        inc  si
;        loop prnwrongparameter
	 lodsb
	 cmp  al,0dh
	 jz   retdos
	 mov  dl,al
;	 mov  ah,02h
	 int  21h
;	 inc  si
	 loop prnwrongparameter
;	 call disp
retdos:
         mov  dl,'"'
	 int  21h
	 mov  dl,'!'
	 int  21h
	 jmp rettodos
reboot:
;         lea  bx,res
	 mov  word ptr [bx],1234h
         lea  bx,dat
	 call dword ptr [bx]
disp:
         mov  ah,09h
	 int  21h
rettodos:	 
	 mov  ah,4ch
	 int  21h
main endp
disp1 proc near
         mov  ah,09h
	 int  21h
	 ret
disp1 endp
;rettodos proc near
 ;        mov  ah,4ch
;	 int  21h
;rettodos endp
 dataseg1 dw ?     	 
 pspseg dw ?
end start
