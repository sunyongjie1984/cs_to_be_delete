;Xboot1.asm HardDisk Self-Protect Program
; tasm xboot1
; tlink xboot1
; exe2bin xboot1
; debug xboot1.exe
; -n xboot1.bin
; -rcx
; :200
; -w cs:0
; -q
; bintodat xboot1.bin xboot1.doc
; bintocat xboot1.bin xboot1.cat
; Ussage:HardDisk Self-Protect program,use a new master boot program,save 
;        the old master boot sector at other sector.If find virus,kill it.
; <<Handbook for HardDisk Protect Technology>> Page 102
PartLoad    equ    600h
TableBegin  equ    7beh
BootLoc     equ    7c00h
IDAddr      equ    7dfeh
           .MODEL  tiny
	   .CODE   
	   org     0
Head:
start:
         cli
	 xor   ax,ax
	 mov   ss,ax
	 mov   sp,7c00h
	 mov   si,sp
	 push  ax
	 pop   es
	 push  ax
	 pop   ds
	 sti
	 cld
	 mov   di,PartLoad
	 mov   cx,100h
	 repne movsw
	 db    0eah
	 dw    offset Continue+600h,0000h
continue:
         push  cs
         pop   ds
         push  cs
         pop   es
         mov   ax,0201h
	 mov   bx,0800h
	 mov   cx,0001h
	 mov   dx,0080h
         pushf
         call  dword ptr [int13_hndlr+0600h]
	 mov   di,0600h
	 mov   si,0800h
	 mov   cx,0100h
	 cld
	 repe  cmpsw
	 jz    @next1
	 mov   si,offset Virus+0600h
	 call  PrintStr
	 mov   ax,0301h
	 mov   bx,0600h
	 mov   cx,0001h
	 mov   dx,0080h
         pushf
	 call  dword ptr [int13_hndlr+0600h]
@next1:
         mov   si,TableBegin
	 mov   bl,4
FindBoot:
         cmp   byte ptr [si],80h
	 je    SaveRec
	 cmp   byte ptr [si],0
	 jne   Invalid
	 add   si,10h
	 dec   bl
	 jnz   FindBoot
	 int   18h
SaveRec:
         mov   dx,[si]
	 mov   cx,[si+2]
	 mov   bp,si
FindNext:
         add   si,10h
	 dec   bl
	 jz    SetRead
	 cmp   byte ptr [si],0
	 je    FindNext
Invalid:
         mov   si,offset ErrMsg1+600h
PrintMsg:
         call  PrintStr
DeadLock:
         jmp   short DeadLock
SetRead:
         mov   di,5
ReadBoot:
         mov   bx,BootLoc
	 mov   ax,201h
	 push  di
	 int   13h
	 pop   di
	 jnc   GoBoot
	 xor   ax,ax
	 int   13h
	 dec   di
	 jnz   ReadBoot
	 mov   si,offset ErrMsg2+600h
	 jmp   short PrintMsg
GoBoot:
         mov   si,offset ErrMsg3+600h
	 mov   di,IDAddr
	 cmp   word ptr [di],0AA55h
	 jne   PrintMsg
	 mov   si,bp
	 db    0EAh,00h,7Ch,00h,00h
ErrMsg1  db    'Invalid partition table. Oh,my god!',0
ErrMsg2  db    'Error loading operating system. Why?',0
ErrMsg3  db    'Missing operating system. Shit!',0
Virus    db    'Master Boot Sector changed.',0ah,0dh
         db    "Don't worry,I have recovered it! Clever! ET-Mouse Yeah!",0ah,0dh,0
PrintStr: 
         lodsb
	 cmp   al,0
	 je    @exit
	 push  si
	 mov   bx,7
	 mov   ah,0Eh
	 int   10h
	 pop   si
	 jmp   short PrintStr
@exit:
         retn
int13_hndlr    label   dword


int13_ofs      dw      09ae4h   ;int 13h offset

int13_seg      dw      0f000h   ;int 13h segment,use int13adr.exe to get it.

Tail:
FillNum  equ   1BEh-(Tail-Head)
         db    FillNum dup (0)
parttable   db  80h, 01h, 01h, 00h, 0bh, 0feh
            db  3fh, 79h, 3fh, 00h, 00h, 00h
	    db  0bbh,0e7h,1dh, 00h, 00h, 00h
	    db  01h, 7ah, 82h, 0feh, 3fh, 80h
	    db  0fah, 0e7h, 1dh, 00h, 47h, 0b7h
	    db  01h, 00h, 00h, 00h, 01h, 81h
	    db  83h, 0feh, 3fh, 0e6h, 41h, 9fh
	    db  1fh,00h, 0e6h, 00h, 19h, 00h
	    db  00h, 00h, 01h,0e7h, 0fh, 0feh
	    db  0bfh,0bh, 27h,0a0h, 38h, 00h
	    db  0a6h,11h, 48h, 00h
MagicID        dw   0AA55h
         end start
	 
	
	 
	 