;mbr-program
;
;masm ptpart.asm
;link ptpart.obj
;exe2bin ptpart
;  debug ptpart.exe
;  -n ptpart.bin
;  -rcx
;  :200
;  -w cs:0
;  -q
;HardDisk Master Boot program
;<<硬盘保护技术手册>> page 22
PartLoad      equ    600h
BootLoc       equ    7C00h
       .MODEL tiny
       .CODE
       org  0
Head:
start:
        cli
	xor  ax,ax
	mov  ss,ax
	mov  sp,7C00h
	mov  si,sp
	push ax
	pop  es
	push ax
	pop  ds
	sti
	cld
	mov  di,PartLoad
	mov  cx,100h
	repne movsw
	db   0EAh
	dw   offset Continue+600H,0000h
Continue:
        mov     si,PartLoad+1BEH
	mov     bl,4
FindBoot:
        cmp    byte ptr[si],80h
	je     SaveRec
	cmp    byte ptr[si],0
	jne    Invalid
	add    si,10h
	dec    bl
	jnz    FindBoot
	int    18h
SaveRec:
        mov  dx,[si]
	mov  cx,[si+2]
	mov  bp,si
FindNext:
        add   si,10h
	dec   bl
	jz    SetRead
	cmp   byte ptr[si],0
	je    FindNext
Invalid:
        mov si,offset ErrMsg1+600h
PrintStr:
        lodsb
	cmp   al,0
	je    DeadLock
	push  si
	mov   bx,7
	mov   ah,0Eh
	int   10h
	pop   si
	jmp   short PrintStr
DeadLock:
        jmp   short DeadLock
SetRead:
        mov   di,5
ReadBoot:
        mov    bx,BootLoc
	mov    ax,201h
	push   di
	int    13h
	pop    di
	jnc    GoBoot
	xor    ax,ax
	int    13h
	dec    di
	jnz    ReadBoot
	mov    si,offset ErrMsg2+600h
	jmp    short PrintStr
GoBoot:
        mov  si,offset ErrMsg3+600h
	mov  di,7C00H+1FEH
	cmp  word ptr[di],0AA55h
	jne  PrintStr
	mov  si,bp
	db   0EAh,00h,7Ch,00h,00h
ErrMsg1 db 'Invalid partition table.',0
ErrMsg2 db 'Error loading operating system.',0
ErrMsg3 db 'Missing operating system.',0
Tail:
FillNum equ  1BEH-(Tail-Head)
        db   FillNum dup(0)
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
MagicID  dw 0AA55h
         END start
	   
	   
	
	
       