;xlock3.asm      --password harddisk lock--
;tasm xlock3
;tlink xlock3
;exe2bin xlock3
;debug xlock3.exe
;-n xlock3.bin
;-r cx
;:200
;-w cs:0
;-q
;bintodat xlock3.bin xlock3.dat
;bintocat xlock3.bin xlock3.cat
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;PAGE 132
;CREAT ON 02/20/1999

partload   equ  600h
tablebegin equ  7beh
bootloc    equ  7c00h
idaddr     equ  7dfeh
passmaxlen    equ  15
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
	mov   di,partload
	mov   cx,100h
	repne movsw
	db    0eah
	dw    offset continue+600h,0000h
	
continue:
        mov   si,tablebegin
	mov   cx,20h
mask1:	
        xor   word ptr [si],0aaaah
	inc   si
	inc   si
	loop  mask1
	mov   ax,0301h
	mov   bx,0600h
	mov   cx,0001h
	mov   dx,0080h
	int   13h
        mov   si,offset readkey+600h
	call  printstr
	mov   di,800h
	call  readstr
	mov   si,800h
	mov   di,offset password+600h
	xor   ch,ch
	mov   cl,byte ptr [di]
	repe  cmpsb
	jz    @next1
	mov   si,offset wrongkey+0600h
	call  printstr
	jmp   $
@next1:
        mov   si,tablebegin
	mov   bl,4
findboot:
        cmp   byte ptr [si],80h
	je    saverec
	cmp   byte ptr [si],0
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
	dec    di
	jnz   readboot
	mov   si,offset errmsg2+600h
	jmp   short printmsg
goboot:
        mov   si,offset errmsg3+600h
	mov   di,idaddr
	cmp   word ptr [di],0aa55h
	jne   printmsg
	mov   si,bp
	db    0eah,00h,7ch,00h,00h
errmsg1    db   'Invalid partition table!',0
errmsg2    db   'Error loading operating system!',0
errmsg3    db   'Missing operating system!',0
readkey    db   'Password:',0
wrongkey   db   'Unauthorized user!',0
plength    db  0
printstr:
        lodsb
	cmp   al,0
	je    @exit
	mov   bh,09h
	push  si
	mov   ah,0eh
	int   10h
	pop   si
	jmp   short printstr
@exit:
        retn
readstr     proc near
        push   es
	push   di
	push   cs
	pop    es
	inc    di
	mov    plength,0
next:
        cmp    plength,passmaxlen
	jge    @l1
	mov    ah,1
	int    16h
	jz     next
	mov    ax,0
	int    16h
	cmp    al,0
	je     next
	cmp    al,08
	je     @l2
	cmp    al,13
	je     @l1
;       sub    al,20
;       or     al,80h
        stosb
	mov    al,'*'
	mov    bx,0
	mov    ah,0eh
	int    10h
	inc    plength
	jmp    next
@l2:
        cmp   plength,0
	je    next
	dec   di
	mov   al,00h
	stosb
	mov   ah,03h
	mov   bh,00h
	int   10h
	dec   dx
	mov   ah,02h
	int   10h
	mov   al,' '
	mov   ah,0eh
	int   10h
	mov   ah,02h
	int   10h
	dec   plength
	dec   di
	jmp   next
@l1:
        pop   di
	mov   al,byte ptr plength
	mov   byte ptr [di],al
	pop   es
	ret
readstr  endp
tail:
fillnum  equ  1beh-(tail-head)-16
         db   fillnum dup(0)
password  db  5,'GAUSS',10 dup(0)

	
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
      end  start
	    