; HardDisk Protect Programe <<硬盘保护技术手册>>page 238
;11:14 98-12-9
; 
;;tasm zkpass
;tlink zkpass
;exe2bin zpkass
;debug zkpass.exe
;-n zkpass.bin
;-rcx
;:200
;-w cs:0
;-q
;bintocat zkpass.bin zkpass.cat

data   segment   at     0h
;                 INT    09H
                 org    9h*4
KeyboardInt      dd     ?
;                 INT    13H
                 org    13H*4
DiskInt          dd     ?
;                 INT    50H
                 org    50h*4
HDInt            dd     ?
                 org    3f0h
ProSeg           dw     ?
                 org    413h
Memory_size      dw     ?
                 org    7C00H
Boot             proc   far
Boot             endp
data             ends
code     segment
         assume    cs:code,ds:data
         org       0h
Head:
         jmp    start
RealInt  label  dword
RealOFF  dw     0a189h
RealCS   dw     0f000h
start:
         cli
	 mov   ax,cs
	 mov   ds,ax
	 mov   es,ax
	 mov   ss,ax
	 mov   sp,7C00h
	 xor   si,si
	 sti
         dec   [Memory_size]
         dec   [Memory_size]
         mov   ax,[Memory_size]
	 mov   cl,6
	 shl   ax,cl
	 mov   es,ax
	 mov   di,0
	 mov   si,7c00h
	 mov   cx,200h
	 rep   movsb
	 push  es
	 mov   ax,offset continue
	 push  ax
	 retf
continue:
         xor   ax,ax
	 mov   ds,ax
         mov   [ProSeg],es
	 cli
	 mov   ax,word ptr [DiskInt]
	 mov   word ptr cs:[RealOFF],ax
	 mov   word ptr [HDInt],ax
	 mov   ax,word ptr [DiskInt+2]
	 mov   word ptr cs:[RealCS],ax
	 mov   word ptr [HDInt+2],ax
	 mov   ax,offset Int_Handler
	 mov   word ptr [DiskInt],ax
	 mov   word ptr [DiskInt+2],cs
	 mov   ax,word ptr [KeyboardInt]
         mov   word ptr cs:[OldInt9],ax
	 mov   ax,word ptr [KeyboardInt+2]
	 mov   word ptr cs:[OldInt9+2],ax
         mov   ax,offset Int9_Handler
	 mov   word ptr [KeyboardInt],ax
	 mov   word ptr [KeyboardInt+2],cs
	 mov   si,0002h
$CheckBoot:	 
	 mov   ax,0201h
	 mov   bx,0200h
	 mov   cx,0001h
	 mov   dx,0080h
	 pushf
         call  dword ptr RealInt
	 jnb   $4
	 dec   si
	 jnz   $CheckBoot
$4:
         xor   si,si
	 mov   di,200h
	 push  cs
	 pop   ds
	 repe  cmpsb
         jz    $Right
	 mov   si,offset Virus_IN
	 xor   ch,ch
	 lodsb
	 mov   cl,al
	 mov   ax,1301h
	 mov   bx,7
	 sub   dx,dx
	 mov   bp,si
	 int   10h
$Right:
         mov   ax,cs
	 mov   es,ax
	 xor   bx,bx
	 mov   ax,0301h
	 mov   cx,0001h
	 mov   dx,0080h
	 pushf
         call  dword ptr RealInt
	 mov   si,0002h
$ReadPass:
         mov   ax,0203h
	 mov   bx,0200h
	 mov   cx,0004h
	 mov   dx,0080h
	 pushf
	 call  dword ptr RealInt
	 jnb   $1
	 dec   si
	 jnz   $ReadPass
$1:
         mov   ax,offset $J1
	 push  ax
	 mov   ax,0200h
	 push  ax
	 ret
$J1:
         sti
	 xor   ax,ax
	 mov   es,ax
	 mov   si,0002h
$RealBoot:
         mov   ax,0201h
	 mov   bx,7c00h
	 mov   cx,0003h
	 mov   dx,0080h
	 pushf
	 call  dword ptr RealInt
	 jnb   $2
	 dec   si
	 jnz   $RealBoot
$2:
         jmp   boot
OldInt9  dd    ?
Virus_IN db    VirusLen,'[Virus] Self Protect...',0ah,0dh
VirusLen equ   ($-Virus_IN)-1
Priority db    00h
         db    0ffh,0ffh
Cyl      dw    482
Hotkey   equ   1
Shift_Mask equ 00001010b
Int_Handler:
         sti
	 cmp   dx,0080h
	 jne   @01
	 cmp   cx,0001h
	 jne   @01
	 mov   cx,0003h
@01:	
         cmp   ah,03h
	 jz    check
	 cmp   ah,05h
         jz    Check
	 cmp   ah,06h
         jz    Check
	 cmp   ah,07h
         jz    Check
	 cmp   ah,0bh
         jz    Check
	 cmp   ah,0fh
         jz    Check
	 cmp   ah,13h
         jz    Check
         cmp   ah,19h
         jz    Check
Conti:
         jmp   cs:[RealInt]
Check:
         cmp   dl,80h
	 jne   conti
         push  cx
         push  dx
         xchg  ch,cl
	 and   ch,11000000b
	 mov   dx,cx
	 mov   cl,6
	 shr   dh,cl
	 cmp   dx,word ptr Cyl
	 pop   dx
	 pop   cx
	 jge   conti
	 cmp   cs:Priority,00h
	 je    Error
	 cmp   dh,00h
	 jne   conti
	 cmp   cx,0001h
	 je    Error
	 cmp   cx,0002h
	 jz    Error
	 cmp   cx,0003h
	 jz    Error
	 cmp   cx,0007h
	 jz    Error
	 cmp   cx,0008h
	 jz    Error
	 jmp   conti
Error:
         mov   ah,03h
	 stc
	 retf  2
Int9_Handler:
         sti
	 push  ax
	 in    al,60h
	 cmp   al,Hotkey
	 je    Trigger
Int9_Exit:	 
         pop   ax
	 jmp   cs:[OldInt9]
Trigger:
         mov   ah,2
	 int   16h
	 and   al,0fh
	 cmp   al,Shift_Mask
	 jnz   Int9_Exit
	 pushf
	 call  cs:[OldInt9]
	 pushf
	 mov   ax,offset @j2
	 push  ax
	 mov   ax,600h
	 push  ax
	 ret
@j2:
         jc    $lock
	 mov   cs:Priority,0ffh
	 jmp   @j3
$lock:
         mov   cs:Priority,00h
@j3:
         popf
	 pop   ax
	 iret
Tail:
Filler_Amount  equ 512-(Tail-Head)-2
         db    Filler_Amount dup(0)
	 dw    0AA55h
code     ends
         end
 
