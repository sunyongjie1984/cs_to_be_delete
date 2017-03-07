; **********************************************************************
; * cmosboot.asm HardDisk Cmos data self reload boot Program           *
; *====================================================================*
; * tasm cmosboot                                                      *
; * tlink cmosboot                                                     *
; * exe2bin cmosboot                                                   *
; * debug cmosboot.exe                                                 *
; * -n cmosboot.bin                                                    *
; * -rcx                                                               * 
; * :200                                                               *
; * -w cs:0                                                            *  
; * -q                                                                 *  
; * bintodat cmosboot.bin cmosboot.doc                                 *
; * bintocat cmosboot.bin cmosboot.cat                                 *
; *                                                                    *  
; **********************************************************************

; **********************************************************************
; * Designer:Howard                                                    * 
; * Creat date:09/13/1999                                              *
; * Original place:Wuhan                                               *
; * Modification date:09/13/1999                                       *
; * Now version: 1.0                                                   *
; **********************************************************************

; **********************************************************************
; *                     Modification History                           *
; *====================================================================*
; * Version 1.0  1.This program is a Master Boot Record.               *
; *  09/13/1999  2.It can reload cmos data to the cmos when boot the   *
; *                the machine from Hard Disk every time               *
; *              3.The cmos data haved backuped to the Hard Disk       *
; *                0 cylinder,0 head,29 sector.                        *
; *              4.Before install this MBR to the Hard Disk,The cmos   *
; *                data must be haved Backuped to the Hard Disk        *
; *              5.The cmos data is only 20 bytes,it is from cmos      *
; *                data address 10h to 2Fh.                            * 
; **********************************************************************         
PartLoad    equ    600h         ;
TableBegin  equ    7beh         ;partition table address in the memory
BootLoc     equ    7c00h        ;dos boot sector loaded to the address
IDAddr      equ    7dfeh        ;dos boot sector ended flag(55aah) 
           .MODEL  tiny
	   .CODE   
	   org     0
Head:
start:
         cli                    ;disable the interrupt (if=0)
	 xor   ax,ax            ;ax=0
	 mov   ss,ax            ;ss=ax
	 mov   sp,7c00h         ;sp=7c00h
	 mov   si,sp            ;si=sp 
	 push  ax               
	 pop   es               ;es=0
	 push  ax
      	 pop   ds               ;ds=0
	 sti                    ;enable the interrupt  (if=1)
	 cld                    ;disable the direction (df=0)
	 mov   di,PartLoad      ;di=600h
	 mov   cx,100h          ;cx=100h (512 bytes=256 words) 
	 repne movsw            ;move the Master Boot Record from 0:7c00 to 0:600
	 db    0eah             ;0eah is far jump code,that is jmp far ptr contiune
	 dw    offset Continue+600h,0000h ;jump to 0:continue+600h

; ************************************************************************
; * The continue code is read the cmos backup data from hard disk sector.*
; * And rewrite the data to cmos.                                        *
; ************************************************************************ 

continue:
         mov   ax,0201h        ;ah=02h,al=01h
         mov   bx,0800h        ;bx=800h,cmos data read to 0:800h
         mov   cx,001dh        ;ch=00h,cl=1dh (the No.29 sector)
         mov   dx,0080h        ;dh=00h (the No.0 head),dl=80h (Hard Disk)
         int   13h
         mov   ax,0010h        ;al=10h cmos unit address
         mov   cx,0020h        ;write 20h bytes cmos data to cmos 
         cld                   ;disable the direction df=0
writecmosdata:
         out   70h,al          ;set the cmos data address
         push  ax              ;the address backup to stack
         mov   al,[bx]         ;al=[bx]
         out   71h,al          ;write a byte data the address
         pop   ax              
         inc   al              ;the next address
         inc   bx              ;the next byte data
         loop  writecmosdata   ;loop
         std                   ;enable the direction df=1
@next1:
         mov   si,TableBegin   ;si=Partition table begin address
	 mov   bl,4            ;4 sets partition data 
FindBoot:
         cmp   byte ptr [si],80h ;Boot partition?
	 je    SaveRec           ;if yes then jump to SaveRec
	 cmp   byte ptr [si],0   ;=0? 
	 jne   Invalid           ;Invalid partition
	 add   si,10h            ;the next partition
	 dec   bl                ;bl-1
	 jnz   FindBoot          ;continue findboot
	 int   18h               ;jump to rom basic
SaveRec:
         mov   dx,[si]
	 mov   cx,[si+2]         ;let Boot partition first sector to cx
	 mov   bp,si             ;bp=si

; ********************************
; * Checked the next partition   *
; ********************************
                                  
FindNext:
         add   si,10h
	 dec   bl
	 jz    SetRead           ;jump to setread
	 cmp   byte ptr [si],0
	 je    FindNext
Invalid:
         mov   si,offset ErrMsg1+600h   ;Errmsg address to si
PrintMsg:
         call  PrintStr                 ;print the msg
DeadLock:
         jmp   short DeadLock           ;Dead lock
SetRead:
         mov   di,5                     ;set reading dos boot sector 5 times

; *******************************************************************
; * read the dos boot sector in order to boot the operating system  *
; *******************************************************************
ReadBoot:
         mov   bx,BootLoc          ;the dos boot sector read to 0:7c00
	 mov   ax,201h             ;ah=02h,al=01h
	 push  di                  ;di pushed to stack(backup the reading times) 
	 int   13h
	 pop   di                  
	 jnc   GoBoot              ;if reading ok then boot the OS
	 xor   ax,ax               ;ax=00h
	 int   13h                 ;reset the driver
	 dec   di                  ;di-1
	 jnz   ReadBoot            ;continue read boot sector
	 mov   si,offset ErrMsg2+600h  ;get errmsg2 address to si
	 jmp   short PrintMsg          ;print the msg
GoBoot:
         mov   si,offset ErrMsg3+600h  ;get errmsg3 address to si
	 mov   di,IDAddr               ;di=boot sector last two bytes
	 cmp   word ptr [di],0AA55h    ;is a boot sector
	 jne   PrintMsg                ;if not boot sector then print errmsg
	 mov   si,bp                   ;si point to bootable partition 
	 db    0EAh,00h,7Ch,00h,00h    ;jump to 0:7c00h

; **********************
; * Error message      *
; **********************
ErrMsg1  db    'Invalid partition table.',0
ErrMsg2  db    'Error loading operating system.',0
ErrMsg3  db    'Missing operating system.',0

PrintStr: 
         lodsb              ;read a byte from [si]
	 cmp   al,0         ;al=0?
	 je    @exit        ;if yes the jump to @exit
	 push  si           ;push si to stack
	 mov   bx,7         ;
	 mov   ah,0Eh       ;display the char 
	 int   10h
	 pop   si          
	 jmp   short PrintStr  ;print the next char
@exit:
         retn                  
Tail:                          ;the Master Boot Record tail
FillNum  equ   1BEh-(Tail-Head)  ;count the fill number
         db    FillNum dup (0)   

; *******************************************************************
; * The Parttition table data                                       *
; * Notise: You must change the next parttition table data to your  *
; *         own Hard Disk parttition table data.                    *
; *******************************************************************
parttable   db  80h,01h,01h,00h,06h,3Fh,7Fh,96h,3Fh,00h
	    db  00h,00h,01h,0Ah,19h,00h,00h,00h,41h,97h,0Fh,3Fh
	    db  0FFh,0FDh,40h,0Ah,19h,00h,00h,0E6h,25h,00h,00h,00h
	    db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	    db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	    db  00h,00h,00h,00h,00h,00h
MagicID        dw   0AA55h
         end start
	 
	
	 
	 