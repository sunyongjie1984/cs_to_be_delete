;软盘引导扇区安装程序
;适用于MS-DOS and PC-DOS 
;can fix virus destory floppy
;<<硬盘保护技术手册>> page 50
   .model tiny
   .code
   org 100h
start:
      jmp begin
Buffer  db 0EBh,37h,90h,47h,61h,75h,73h,73h,44h,73h,6Bh,00h
        db 02h,01h,01h,00h,02h,0E0h,00h,60h,09h,0F9h,07h,00h
        db 0Fh,00h,02h,00h,00h,00h,00h,00h,00h,00h,00h,00h
        db 0Fh,00h,00h,00h,00h,01h,00h,00h,00h,00h,00h,00h
        db 00h,01h,01h,00h,01h,0Fh,1Dh,00h,00h,0FAh,0FCh,33h
        db 0C0h,8Eh,0D0h,0BCh,00h,7Ch,36h,0C5h,36h,78h,00h,1Eh
        db 56h,8Eh,0C0h,8Dh,3Eh,20h,7Ch,0B9h,0Bh,00h,0ACh,26h
        db 80h,3Dh,00h,74h,03h,26h,8Ah,05h,0AAh,0E2h,0F3h,33h
        db 0C0h,8Eh,0D8h,0A3h,7Ah,00h,0C7h,06h,78h,00h,20h,7Ch
        db 0FBh,0CDh,13h,73h,03h,0E9h,0B4h,00h,8Ah,2Eh,30h,7Ch
        db 8Ah,0Eh,32h,7Ch,8Ah,36h,31h,7Ch,0B2h,00h,0BBh,00h
        db 05h,0B8h,01h,02h,0CDh,13h,72h,0E5h,8Dh,36h,5Bh,7Dh
        db 8Bh,0FBh,0B9h,0Bh,00h,0F3h,0A6h,75h,0Dh,0BFh,20h,05h
        db 0B9h,0Bh,00h,0F3h,0A6h,74h,1Ah,0E9h,89h,00h,8Dh,36h
        db 6Fh,7Dh,8Bh,0FBh,0B9h,0Bh,00h,0F3h,0A6h,75h,7Ch,0BFh
        db 20h,05h,0B9h,0Bh,00h,0F3h,0A6h,75h,72h,33h,0D2h,0A1h
        db 1Ch,05h,0F7h,36h,0Bh,7Ch,0FEh,0C0h,0A2h,38h,7Ch,0BBh
        db 00h,07h,8Ah,2Eh,33h,7Ch,8Ah,0Eh,35h,7Ch,8Ah,36h
        db 34h,7Ch,0B2h,00h,0A1h,18h,7Ch,2Ah,0C1h,0FEh,0C0h,50h
        db 0B4h,02h,0CDh,13h,58h,72h,3Dh,28h,06h,38h,7Ch,76h
        db 1Ah,0B4h,00h,52h,0F7h,26h,0Bh,7Ch,5Ah,03h,0D8h,0B1h
        db 01h,0FEh,0C6h,3Ah,36h,1Ah,7Ch,72h,0D7h,0FEh,0C5h,0B6h
        db 00h,0EBh,0D1h,0CDh,11h,0D0h,0C0h,0D0h,0C0h,25h,03h,00h
        db 75h,01h,40h,40h,8Bh,0C8h,0B8h,00h,00h,0B2h,00h,8Bh
        db 1Eh,36h,7Ch,0EAh,00h,00h,70h,00h,8Dh,36h,83h,7Dh
        db 0EBh,05h,90h,8Dh,36h,98h,7Dh,0ACh,0Ah,0C0h,74h,09h
        db 0BBh,07h,00h,0B4h,0Eh,0CDh,10h,0EBh,0F2h,8Dh,1Eh,0B9h
        db 7Dh,3Bh,0F3h,77h,04h,8Bh,0F3h,0EBh,0E6h,32h,0E4h,0CDh
        db 16h,8Fh,06h,78h,00h,8Fh,06h,7Ah,00h,0CDh,19h,49h
        db 42h,4Dh,42h,49h,4Fh,20h,43h,4Fh,4Dh,49h,42h,4Dh
        db 44h,4Fh,53h,20h,43h,4Fh,4Dh,49h,4Fh,20h,20h,20h
        db 20h,20h,53h,59h,53h,4Dh,53h,44h,4Fh,53h,20h,20h
        db 53h,59h,53h,0Ah,0Dh,44h,69h,73h,6Bh,20h,42h,6Fh
        db 6Fh,74h,20h,46h,61h,69h,6Ch,75h,72h,65h,21h,00h
        db 0Ah,0Dh,4Eh,6Fh,6Eh,2Dh,53h,79h,73h,74h,65h,6Dh
        db 20h,64h,69h,73h,6Bh,20h,6Fh,72h,20h,64h,69h,73h
        db 6Bh,20h,65h,72h,72h,6Fh,72h,21h,00h,0Ah,0Dh,52h
        db 65h,70h,6Ch,61h,63h,65h,20h,61h,6Eh,64h,20h,70h
        db 72h,65h,73h,73h,20h,61h,6Eh,79h,20h,77h,68h,65h
        db 6Eh,20h,72h,65h,61h,64h,79h,2Eh,2Eh,2Eh,0Ah,0Dh
        db 2Ah,2Ah,2Ah,20h,47h,61h,75h,73h,73h,20h,30h,38h
        db 2Fh,31h,30h,2Fh,39h,38h,20h,2Ah,2Ah,2Ah,0Ah,0Dh
        db 00h,00h,00h,00h,00h,00h,55h,0AAh
Type1   db 00h,02h,02h,01h,00h,02h,70h,00h,0D0h,02h,0FDh,02h
        db 00h,09h,00h,02h,00h,00h,00h,00h, 00h,00h, 00h,00h
        db 00h,0Fh,00h,00h,00h,00h,01h,00h, 00h,00h, 00h,00h
        db 00h,00h,00h,06h,00h,01h,04h,0Ch, 00h
Type2   db 00h,02h,01h,01h,00h,02h,0E0h,00h,60h,09h,0F9h,07h
        db 00h,0Fh,00h,02h,00h,00h, 00h,00h,00h,00h, 00h,00h
        db 00h,0Fh,00h,00h,00h,00h, 01h,00h,00h,00h, 00h,00h
        db 00h,00h,01h,01h,00h,01h, 0Fh,1Dh,00h
Type3   db 00h,02h,01h,01h,00h,02h,0E0h,00h,40h,0Bh,0F0h,09h
        db 00h,12h,00h,02h,00h,00h, 00h,00h,00h,00h, 00h,00h
        db 00h,0Fh,00h,00h,00h,00h, 01h,00h,00h,00h, 00h,00h
        db 00h,00h,01h,02h,00h,01h, 10h,21h,00h
T_OFS   dw offset type1
        dw offset type2
        dw offset type3
askmsg1 db ' __________________________________________________ ',0ah,0dh
        db '|   **** Boot Sector Recover Utility v1.0 ****     |',0ah,0dh
        db '|--------------------------------------------------|',0ah,0dh
        db '|   This program is used to recover the diskette   |',0ah,0dh
        db '| damaged by any type System Virus such as (C)Bra- |',0ah,0dh
        db '| in,DiskKiller,Stone,Copy Lock,or other native    |',0ah,0dh
        db '| system virus desighed by evil PC-fan user.(*_*)  |',0ah,0dh
        db '|--------------------------------------------------|',0ah,0dh
        db '| (C) ETMouseSoft Co.Inc. Made by ETMouse 08/10/98 |',0ah,0dh
        db '|__________________________________________________|',0ah,0dh
        db '          Do you want to proceed?  (Y/N)      ',07h,'$'
askmsg2 db ' __________________________________________________ ',0dh,0ah
        db '|   **** Boot Sector Recover Utility v1.0 ****     |',0dh,0ah
        db '|--------------------------------------------------|',0dh,0ah
        db '|   This program is used to recover the diskette   |',0dh,0ah
        db '| damaged by any type System Virus such as (C)Bra- |',0dh,0ah
        db '| in,DiskKiller,Stone,Copy Lock,or other native    |',0dh,0ah
        db '| system virus desighed by evil PC-fan user.(*_*)  |',0dh,0ah
        db '|--------------------------------------------------|',0dh,0ah
        db '| (C) ETMouseSoft Co.Inc. Made by ETMouse 08/10/98 |',0dh,0ah
        db '|__________________________________________________|',0ah,0dh
        db '          Do you want to proceed?  (Y/N)      ',07h,'$'
askmsg  dw askmsg1,askmsg2
Media   db 0dh,0ah,'(1)360K (2)1.2M (3)1.44M (1/2/3)','$'
sucmsg1 db 0dh,0ah,'Recover sucessfully!',07h,'$'
sucmsg2 db 0dh,0ah,'Recover sucessfully!',07h,'$'
sucmsg  dw sucmsg1,sucmsg2
errmsg1 db 0dh,0ah,'Drive A Write Error,Check the Floppy...',07h,'$'
errmsg2 db 0dh,0ah,'Drive A Write Error,Check the Floppy...',07h,'$'
errmsg  dw errmsg1,errmsg2
CheckET Proc
        mov ax,9100h
        int 10h
        cmp ax,9100h
        jne true
        mov di,0
        ret
true:
        mov di,2
        ret
CheckEt endp
begin:
        push cs
        pop  ds
        push cs
        pop  es
        call CheckET
        mov  ah,09h
        mov  dx,word ptr askmsg[di]
        int  21h
echo:
        mov  ah,07h
        int  21h
        cmp  al,'Y'
        je   Check_Media
        cmp  al,'y'
        je   Check_Media
        jmp  exit
Check_Media:
        mov  ah,09h
        mov  dx,offset Media
        int  21h
p1:
        mov  ah,07h
        int  21h
        cmp  al,'1'
        je   dtype1
        cmp  al,'2'
        je   dtype2
        cmp  al,'3'
        je   dtype3
        jmp  p1
dtype1:
        mov  si,[word ptr T_OFS]
        mov  di,offset buffer+11
        mov  cx,2dh
        rep  movsb
        jmp  short install
dtype2:
        mov  si,[word ptr T_OFS+2]
        mov  di,offset buffer+11
        mov  cx,2dh
        rep  movsb
        jmp  short install
dtype3:
        mov  si,[word ptr T_OFS+2]
        mov  di,offset buffer+11
        mov  cx,2dh
        rep  movsb
install:
        mov  si,5
        push cs
        pop  es
writeboot:
        push si
        mov  ax,0301h
        mov  bx,offset buffer
        mov  cx,0001h
        mov  dx,0
        int  13h
        pop  si
        jnc  sucess
        dec  si
        jnz  writeboot
error:
        call CheckET
        mov  ah,09h
        mov  dx,word ptr errmsg[di]
        int  21h
        jmp  exit
sucess:
        call CheckET
        mov  ah,09h
        mov  dx,word ptr sucmsg[di]
        int  21h
exit:
        mov  ah,4ch
        int  21h
        end start

