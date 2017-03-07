; HardDisk Protection Programe <<硬盘保护技术手册>>page 201
; 使用模拟的int 13h 中断调用方式
;用int 50h保存int 13h中断位置
;有只读与可读写两种状态
;self protection

;tasm zpass
;tlink zpass
;exe2bin zpass
;debug zpass.exe
;-n zpass.bin
;-rcx
;:200
;-w cs:0
;-q
;bintocat zpass.bin zpass.cat

;定义各中断数据扇区段,由段址0000开始
data   segment   at     0h
;keyboardint position  INT    09H
                 org    9h*4
KeyboardInt      dd     ?
;diskint_pos  INT    13H
                 org    13H*4
DiskInt          dd     ?
;to keep the HDint_pos INT    50H
                 org    50h*4
HDInt            dd     ?
                 org    3f0h
ProSeg           dw     ?
;Keep the sizes of memory position
                 org    413h
Memory_size      dw     ?
                 org    7C00H ;Boot Sector loaded address
Boot             proc   far
Boot             endp
data             ends
code     segment
         assume    cs:code,ds:data
         org       0h
Head:
         jmp    start
;Keep the old INT 13H interrupt position
RealInt  label  dword
RealOFF  dw     0a189h
RealCS   dw     0f000h
start:
         cli
	 mov   ax,cs   ;ax=cs=0           
	 mov   ds,ax   ;ds=ax=0
	 mov   es,ax   ;es=ax=0
	 mov   ss,ax   ;ss=ax=0
	 mov   sp,7C00h   ;sp=7c00h
	 xor   si,si   ;si=0
	 sti
         dec   [Memory_size]   ;将记载内存大小位置减少2k
         dec   [Memory_size]
         mov   ax,[Memory_size]   ;ax=memory_size k
	 mov   cl,6
	 shl   ax,cl   ;算出启始的段址
	 mov   es,ax   ;keep ax to es
	 mov   di,0    ;di=0
	 mov   si,7c00h   ;将0:7c00h开始的200h bytes move to es:0 的高端
	 mov   cx,200h
	 rep   movsb
	 push  es
	 mov   ax,offset continue
	 push  ax   ;jump to es:continue
	 retf
continue:
         xor   ax,ax   ;ax=0
	 mov   ds,ax   ;ds=0
         mov   [ProSeg],es   ;keep the value of es to 0:3foh
	 cli
;keep old int 13h position to realint and int 50h
	 mov   ax,word ptr [DiskInt]
	 mov   word ptr cs:[RealOFF],ax
	 mov   word ptr [HDInt],ax
	 mov   ax,word ptr [DiskInt+2]
	 mov   word ptr cs:[RealCS],ax
	 mov   word ptr [HDInt+2],ax
;set new driver interrupt position
	 mov   ax,offset Int_Handler
	 mov   word ptr [DiskInt],ax
	 mov   word ptr [DiskInt+2],cs
;set new keyboad interrupt position
	 mov   ax,word ptr [KeyboardInt]
         mov   word ptr cs:[OldInt9],ax
	 mov   ax,word ptr [KeyboardInt+2]
	 mov   word ptr cs:[OldInt9+2],ax
         mov   ax,offset Int9_Handler
	 mov   word ptr [KeyboardInt],ax
	 mov   word ptr [KeyboardInt+2],cs
;read No.1 sector
	 mov   si,0002h   ;set times of reread 2
$CheckBoot:	 
	 mov   ax,0201h   ;read to es:0200h position
	 mov   bx,0200h
	 mov   cx,0001h
	 mov   dx,0080h
	 pushf
         call  dword ptr RealInt   ;simulation int 13h interrupt
	 jnb   $4
	 dec   si
	 jnz   $CheckBoot
;check the sector to be change or not
$4:
         xor   si,si   ;si=0
	 mov   di,200h   ;di=0200h
	 push  cs   ;ds=cs
	 pop   ds
	 repe  cmpsb
         jz    $Right
;if the value of sector is changed,write the old value of the sector to the sector
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
;read password check program segment and each subprogram to es:0200h
	 mov   si,0002h   ;set read times 2
$ReadPass:
         mov   ax,0203h   ;read 3 sectors
	 mov   bx,0200h   ;read to es:0200h
	 mov   cx,0004h   ;from No.4 sector to begin
	 mov   dx,0080h   
	 pushf            ;simulation int 13h interrupt
	 call  dword ptr RealInt
	 jnb   $1
	 dec   si
	 jnz   $ReadPass
$1:                        ;simulation CALL calls
         mov   ax,offset $J1
	 push  ax
	 mov   ax,0200h   ;CALL 0200h
	 push  ax
	 ret
$J1:
;read old master boot program to 0:7c00h
         sti
	 xor   ax,ax
	 mov   es,ax
	 mov   si,0002h   ;set read times
$RealBoot:
         mov   ax,0201h   ;read one sector
	 mov   bx,7c00h   ;read to 0:7c00h
	 mov   cx,0003h   ;number of sector is 3.
	 mov   dx,0080h
	 pushf            ;simulation int 13h call
	 call  dword ptr RealInt
	 jnb   $2
	 dec   si
	 jnz   $RealBoot
$2:
         jmp   boot   ;jump to normal boot process			
OldInt9  dd    ?
;show the virus destroy infomation
Virus_IN db    VirusLen,'[Virus] Self Protect...',0ah,0dh
VirusLen equ   ($-Virus_IN)-1
;set user authority
Priority db    00h
         db    0ffh,0ffh
;logic disk d begin sector
Cyl      dw    482
Hotkey   equ   1   ;set hotkey as shift-alt-esc
Shift_Mask equ 00001010b
;new int 13h driver interrupt service program
Int_Handler:
         sti
	 cmp   dx,0080h   ;if it read master boot sector,set it to read No.3 sector
	 jne   @01
	 cmp   cx,0001h
	 jne   @01
	 mov   cx,0003h
@01:	
         cmp   ah,03h   ;intercept each write and format operating
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
         cmp   dl,80h   ;if it isn't disk c and continue
	 jne   conti
	 cmp   cs:Priority,00h   ;set write protect pointer or not
	 je    Error   ;if write protect is on,shut down the write operating
	 cmp   dh,00h   ;if write protect is off,only protect some important sectors
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
	 in    al,60h   ;read the key code
	 cmp   al,Hotkey   ;judge it is key esc or not
	 je    Trigger
Int9_Exit:	 
         pop   ax
	 jmp   cs:[OldInt9]   ;if not and leave
Trigger:
         mov   ah,2   ;judge the keys press SHIFT-ALT 
	 int   16h
	 and   al,0fh
	 cmp   al,Shift_Mask
	 jnz   Int9_Exit   ;if not and leave
	 pushf
	 call  cs:[OldInt9]
	 pushf             ;saved the flag
	 mov   ax,offset @j2
	 push  ax
	 mov   ax,600h   ;call the password checking program at 0600h
	 push  ax
	 ret
@j2:
         jc    $lock   ;set write protect
	 mov   cs:Priority,0ffh
	 jmp   @j3
$lock:
         mov   cs:Priority,00h   ;set write and read status
@j3:
         popf     ;resume the value of flag and ax
	 pop   ax
	 iret
Tail:
Filler_Amount  equ 512-(Tail-Head)-2
         db    Filler_Amount dup(0)
	 dw    0AA55h
code     ends
         end
 
