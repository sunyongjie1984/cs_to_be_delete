;mboot.asm  --- Multi-Operating System Boot program
;tasm mboot
;tlink mboot
;exe2bin mboot
;debug mboot.exe
;-n mboot.bin
;-r cx
;:200
;-w cs:0
;-q
;bintodat mboot.bin mboot.dat
;Usage: This program is used to replace the Master Boot Sector,
;       make the Mbr can boot multi operating system.
;Book:  HARDDISK PROTECTION TECHNIQUE HANDBOOK
;PAGE: 150
;CREAT ON 02/21/1999


       .MODEL TINY
       .CODE
cr     equ  0dh
lf     equ  0ah
bootloc     equ  7c00h
adjust      equ  600h
base        equ  $
       org       0h

begin:
       cli
       xor   ax,ax
       mov   ss,ax
       mov   sp,offset bootloc
       mov   si,sp
       push  ax
       pop   es
       push  ax
       pop   ds
       sti
       cld
       mov   di,600h
       mov   ax,100h
       rep   movsw
       mov   ax,offset relboot+adjust
       push  ax
       ret

relboot:
       mov   byte ptr p1+adjust,0
       mov   byte ptr p2+adjust,0
       mov   byte ptr p3+adjust,0
       mov   byte ptr p4+adjust,0

wrprmpt:
       mov   si,offset msg4+adjust
       call  printzstr
       mov   al,' '
       mov   cl,1
       mov   ah,10
       int   10
       mov   ah,0
       int   16h
       and   al,7fh-20h
       push  ax
       mov   ah,10
       mov   cx,1
       int   10h
       pop   ax
       cmp   al,'W'
       je    lddos
       cmp   al,'L'
       je    linux
       jmp   wrprmpt
       
       
lddos:
       mov   al,6      ;check the dos partition table,change the system id when necessary

       mov   si,offset dosnm+adjust
       jmp   short gotact1
       
linux:
       mov   al,2
       mov   si,offset linuxnm+adjust
       
gotact1:
       mov   di,offset msg5nm+adjust
       mov   cx,6
       cld   
       rep   movsb
       mov   bl,4
       mov   si,offset parttb1+adjust
       
       
getpart_a:
       cmp   byte ptr[si+4],al
       je    gotact2
       add   si,16
       dec   bl
       jnz   getpart_a
       mov   si,offset msg5+adjust
       call  printzstr
       
lupe1:
       jmp   lupe1

gotact2:
       mov   byte ptr[si],80h
       push  si
       push  bx
       mov   ax,0301h
       mov   bx,600h
       mov   cx,1
       mov   dx,80h
       int   13h
       pop   bx
       pop   si
       
gotact:
       mov   dx,[si]
       mov   cx,[si+2]
       mov   bp,si
finis:
       mov   di,5
rdboot:
       mov   bx,bootloc
       mov   ax,0201h
       int   13h
       jnc   goodrd
       xor   ax,ax
       int   13h
       dec   di
       jnz   rdboot
       mov   si,offset msg2+adjust
       
wrmsg:
       call  printzstr
lupe:
       jmp   lupe
       
goodrd:
       mov   si,offset msg3+adjust
       cmp   word ptr bootsig,0aa55h
       jne   wrmsg
       mov   si,bp
       mov   ax,offset bootloc
       push  ax
       ret
       
msg2     db  lmsg2,'Error loading operating system!'
lmsg2    equ ($-msg2)-1
msg3     db  lmsg3,'Missing operating system!'
lmsg3    equ ($-msg3)-1
msg4     db  lmsg4,'(C)opyright Howard Dream-lives.',0dh,0ah
         db  'MultiOS Master boot program',0dh,0ah
	 db  'Input L=Linux,W=Windows'
lmsg4    equ ($-msg4)-1
msg5     db  lmsg5,'Cannot find '
msg5nm   db  'xxxxxxx'
lmsg5    equ ($-msg5)-1
dosnm    db  'Windows'
linuxnm  db  'Linux'

printzstr:
         mov   bh,0
	 mov   ah,03h
	 int   10h
	 xor   ch,ch
	 lodsb
	 mov   cl,al
	 mov   bx,9
	 mov   ax,1301h
	 mov   bp,si
	 int   10h
	 retn
tail     equ   $
fillnum  equ   1beh-(tail-base)
         db    fillnum dup(0)
	 org   base+1beh
	 
parttb1  equ   byte ptr base+1beh
p1       equ   base+1beh
p2       equ   p1+16
p3       equ   p2+16
p4       equ   p3+16
signat   equ   p4+16
bootsig  equ   base+7dfeh
         org   base+512-2
magicid  dw    0aa55h
         end   begin