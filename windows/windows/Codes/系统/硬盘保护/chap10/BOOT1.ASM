;This program is used to install to the floppy boot sector,     ---boot1.asm
;it makes the floppy boot from harddisk.
;masm   boot1
;link   boot1
;exe2bin boot1
;debug boot1.exe
;-n boot1.bin
;-r cx
;:200
;-w cs:0
-q
;bintodat boot1.bin boot1.dat
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;PAGE: 164
;CREAT ON 02/21/1999



data    segment  at  0h
        org   7c00h
boot    proc  far
boot    endp
data    ends
cseg    segment   'code'
        assume    cs:cseg,ds:data,es:data
	org     0h
	
	
head:
       jmp   begin
;this data is BPB(BIOS PARAMETRT BLOCK) (1.44m FLOPPY)       
       db    'Howard '
       dw    0200h
       db    01h
       dw    0001h
       db    02h
       dw    00e0h
       dw    0b40h
       db    0f0h
       dw    0009h
       dw    0012h
       dw    0002h
       dw    0
       
       db    14 dup (0)
       
begin:
       cli
       xor   ax,ax
       mov   ss,ax
       mov   sp,7c00h
       mov   si,sp
       push  ax
       pop   es
       push  ax
       pop   ds
       cld
       mov   di,0600h
       mov   cx,0100h
       repnz movsw
       xor   ax,ax
       push  ax
       mov   ax,offset conti+600h
       push  ax
       retf

conti:
       mov   di,offset beg_message+0600h
       call  put_str
       mov   ax,0201h
       mov   bx,7c00h
       mov   cx,0001h
       mov   dx,0080h
       int   13h
       jmp   boot
       
beg_message:
       db ' ________________________________________',0dh,0ah
       db '|     *** Harddisk booter floppy ***     |',0dh,0ah
       db '|========================================|',0dh,0ah
       db '|           Version 1.00                 |',0dh,0ah
       db '|    This diskette is forced to boot     |',0dh,0ah
       db '|    from the Hard Disk...               |',0dh,0ah
       db '|              by Howard, 02/21/1999     |',0dh,0ah
       db '|________________________________________|',0dh,0ah,'$'

end_message: 

put_str   proc
       mov   al,cs:[di]
       cmp   al,'$'
       je    a1
       mov   ah,0eh
       mov   bx,0003h
       int   10h
       inc   di
       jmp   put_str
a1: 
       ret
put_str   endp

tail:
filler_amount   equ   512-(tail-head)-2
        db   filler_amount dup(0)
	db   055h,0aah
cseg    ends
        end