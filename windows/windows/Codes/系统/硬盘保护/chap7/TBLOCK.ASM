;tblock.asm
;tasm tblock
;tlink tblock
;exe2bin tblock
;debug tblock.exe
;-n tblock.bin
;-r cx
;:200
;-w cs:0
;-q
;bintodat tblock.bin tblock.doc
;bintocat tblock.bin tblock.cat
;This program is simple one sector harddisk cipher hidden program;
;master boot and check the password
;book:HARDDISK PROTECTION TECHNIQUE HANDBOOK
;page 118
;if someone boot from drive a:,it can't find the harddisk.
PartLoad   equ  600h
TableBegin equ  7beh
BootLoc    equ  7c00h
IDAddr     equ  7dfeh
        .model tiny
	.code
	org    0
head:
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
Continue:
	mov   si,tablebegin
;	mov   si,offset readkey+0600h
;	call  printstr
	;mov   ah,0
	;int   16h
	;cmp   ah,82
	;je    @next1
	;mov   si,offset wrongkey+0600h
	;call  printstr
	;jmp   $
	mov   cx,20h
mask:
        xor   word ptr [si],0aaaah
	inc   si
	inc   si
	loop  mask
	mov   ax,0301h
	mov   bx,0600h
	mov   cx,0001h
	mov   dx,0080h
	int   13h
	mov   si,tablebegin
	mov   bl,4

        
	 
findboot:
        cmp   byte ptr [si],80h
	je    saverec
	cmp   byte ptr[si],0
	jne   invalid
	add   si,10h
	dec   bl
	jnz   findboot
	int   18h
saverec:
        mov   dx,[si]
	mov   cx,[si+2]
	mov   bp,si
findnext:
        add   si,10h
	dec   bl
	jz    setread
	cmp   byte ptr [si],0
	je    findnext
invalid:
        mov   si,offset errmsg1+600h
printmsg:
        call  printstr
deadlock:
        jmp   short deadlock
setread:
        mov   di,5
readboot:
        mov   bx,bootloc
	mov   ax,201h
	push  di
	int   13h
	pop   di
	jnc   goboot
	xor   ax,ax
	int   13h
	dec   di
	jnz   readboot
	mov   si,offset errmsg2+600h
	jmp   short printmsg
goboot:
        mov   si,offset errmsg3+600h
        mov   di,IDAddr
	cmp   word ptr[di],0aa55h
	jne   printmsg
	mov   si,bp
	db    0eah,00h,7ch,00h,00h
errmsg1 db  'Invalid partition table!',0
errmsg2 db  'Error loading operating system!',0
errmsg3 db  'Missing operating system!',0
readkey db  'Press passkey to continue:',0ah,0dh,0
wrongkey db 'Unauthorized User!',0
printstr:
        lodsb
	cmp   al,0
	je    @exit
	push  si
	mov   bx,7
	mov   ah,0eh
	int   10h
	pop   si
	jmp   short printstr
@exit:
        retn
tail:
fillnum  equ  1beh-(tail-head)
         db   fillnum dup(0)
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
magicid     dw  0aa55h
      end start
	    

	