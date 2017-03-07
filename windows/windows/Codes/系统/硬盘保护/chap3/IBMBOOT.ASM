;IBMBOOT.ASM
;MASM IBMBOOT
;LINK IBMBOOT
;DEBUG
;-N IBMBOOT.BIN
;-RCX
;200
;-W CS:7C00
;-Q
;bintodat ibmboot.bin ibmboot.out
;fix floppy boot sector 
;floppy boot program
;<<硬盘保护技术手册>> page 44

dskpara    equ  1Eh*4
iohead     equ  500h
iosize     equ  51Ch
doshead    equ  520h
ioload     equ  700h
cseg       segment byte public
           assume  cs:cseg,ds:cseg
           org     7c00h
Head:
IBMBoot    proc  far
Start:     jmp short Begin
           db   90h
MyID       db   'GaussDsk'
SecInByte  dw   0200h
SecPerClr  db   01h
ResClr     dw   0001h
NumOfFat   db   02h
RootEnpty  dw   00E0h
TotalSec   dw   0960h
FormatID   db   0F9h
SecPerFat  dw   0007h
SecPerTrk  dw   000Fh
Sides      dw   0002h
Hsector    dw   0000h
           db   2 dup(0)
DiskParaFix db 00h,00h,00h,00h,0Fh,00h,00h,00h
            db 00h,01h,00h,00h,00h,00h,00h,00h
RootTrack   db 00h
RootHead    db 01h
RootSecNo   db 01h
IoTrack     db 00h
IoHeadNo    db 01h
IoSecNo     db 0Fh
FirstDataSec dw 001Dh
Temp        db 00h
Begin:
        cli
        cld
        xor ax,ax
        mov ss,ax
        mov sp,7C00h
        lds si,dword ptr ss:dskpara
        push ds
        push si
        mov es,ax
        lea di,DiskParaFix
        mov cx,0Bh
FixParam:
        lodsb
        cmp byte ptr es:[di],0
        je  NotCare
        mov al,es:[di]
NotCare:
        stosb
        loop FixParam
        xor ax,ax
        mov ds,ax
        mov word ptr ds:dskpara+2,ax
        mov word ptr ds:dskpara,7C20h
        sti
        int 13h
        jnc Success
ErrEntry:
        jmp BootErr 
Success:
        mov ch,RootTrack
        mov cl,RootSecNo
        mov dh,RootHead
        mov dl,0
        mov bx,iohead
        mov ax,201h
        int 13h
        jc  ErrEntry
        lea si,PCDOS1
        mov di,bx
        mov cx,0Bh
        repe cmpsb
        jnz CmpMsdos
        mov di,doshead
        mov cx,0Bh
        repe cmpsb
        jz  BootDisk
        jmp NonSysErr
CmpMsdos:
        lea  si,MSDOS1
        mov  di,bx
        mov  cx,0Bh
        repe cmpsb
        jnz  NonSysErr
        mov  di,doshead
        mov  cx,0Bh
        repe cmpsb
        jnz  NonSysErr
BootDisk:
        xor dx,dx
        mov ax,ds:iosize
        div word ptr SecInByte
        inc al
        mov Temp,al
        mov bx,ioload
        mov ch,IoTrack
        mov cl,IoSecNo
        mov dh,IoHeadNo
        mov dl,0
ReadAgain:
        mov ax,SecPerTrk
        sub al,cl
        inc al
        push ax
        mov  ah,2
        int 13h
        pop ax
        jc   BootErr
        sub  Temp,al
        jbe  ReadEnd
        mov  ah,0
        push dx
        mul word ptr SecInByte
        pop dx
        add bx,ax
        mov cl,1
        inc dh
        cmp dh,Byte ptr Sides
        jb  ReadAgain
        inc ch
        mov dh,0
        jmp short ReadAgain
ReadEnd:
        int  11h
        rol  al,1
        rol  al,1
        and  ax,3
        jnz  NoZero
        inc  ax
NoZero:
        inc ax
        mov cx,ax
        mov ax,0
        mov dl,0
        mov bx,FirstDataSec
        db  0EAh,00h,00h,70h,00h
BootErr:
        lea si,BootError
        jmp short Print
        db  90h
NonSysErr:
        lea si,NonSystem
Print:
        lodsb
        or  al,al
        jz  EndStr
        mov bx,7
        mov ah,0Eh
        int 10h
        jmp  short Print
EndStr:
        lea bx,Repl
        cmp si,bx
        ja  PrintEnd
        mov si,bx
        jmp short Print
PrintEnd:
        xor ah,ah
        int 16h
        pop word ptr ds:dskpara
        pop word ptr ds:dskpara+2
        int 19h
PCDOS1 db 'IBMBIO COM'
PCDOS2 db 'IBMDOS COM'
MSDOS1 db 'IO     SYS'
MSDOS2 db 'MSDOS  SYS'
BootError db 0Ah,0Dh,'Disk Boot Failure!',0
NonSystem db 0Ah,0Dh,'Non-System disk or disk error!',0
Repl      db 0Ah,0Dh,'Replace and press any when ready...',0Ah,0Dh
          db '*** Gauss 08/10/98 ***',0Ah,0Dh,0
Tail:
Filler_Amount equ 512-(Tail-Head)-2
              db Filler_Amount dup(0)
BootID  db 55h,0AAh
IBMboot endp
cseg    ends
        end Start
