;HardDisk lock Data Lib
;Begin at 0200h show the title
;At 0600h Hotkey and password checking program
;zpass1.asm HardDisk lock sub program load in 0 cys 4,5,6 sectors
;Book page244
;Line 61 error
;check 11:15 98-12-9
;tasm zkpass1
;tlink zkpass1
;debug zkpass1.exe
;-rcx
;:600
;-w cs:200
;-n zkpass1.bin
;-q
;bintocat zkpass1.bin zkpass1.cat

             .MODEL tiny
	     .CODE
DISKIO       equ    13h
VIDEO        equ    10h
             ORG    200h
GetPassWord Proc
PassBegin:
MyRoutine:
        push  cs
	pop   ds
	mov   di,offset HeadMsg
	call  Put_Str
	mov   cx,10000
$l1:
        nop   
	loop  $l1
	ret
	
	
Put_Str	proc
        mov   al,cs:[di]
	cmp   al,'$'
	je    A1
	mov   ah,0eh
	mov   bx,0003h
	int   video
	inc   di
	jmp   Put_Str
A1:
        ret
Put_Str endp
;PLength db 0
HeadMsg db " __________________________________________________",0ah,0dh
        db "|	     HardDisk Write Protect Program 	       |",0ah,0dh
	db "|     Use hot-key and input the password,you can   |",0ah,0dh
	db "|  set the Write & Read status.You can not boot    |",0ah,0dh
	db "|  the computer from floppy.It can protect your    |",0ah,0dh
	db "|  harddisk from virus destory.You can reset the   |",0ah,0dh
	db "|  password and remove the password(Use setpass.   |",0ah,0dh
	db "|  exe & HDremove.exe).The user can use the com-   |",0ah,0dh
	db "|  puter,even he or she doesn'tknows the password. |",0ah,0dh
	db "|__________________________________________________|",0ah,0dh
        db " __________________________________________________	",0ah,0dh
	db "|  *** HardDisk Anti-Virus & Security System ***   |",0ah,0dh
	db "|--------------------------------------------------|",0ah,0dh
	db "|             ET-Mouse SoftWare WorkShop 12/1998   |",0ah,0dh
	db "|__________________________________________________|",0ah,0dh
	db " __________________________________________________ ",0ah,0dh
	db "|      ** Protect Logical Driver C Only **	       |",0ah,0dh
	db "|__________________________________________________|",0ah,0dh
	;db         0ah,0dh
	;db         'Password:','$'
Passtail:
PassLen  equ     1024-(Passtail-PassBegin)
         db      PassLen dup (0)
	 ;org     PassBegin+1024
GetPassword	 endp
         org     600h
GetPass  Proc
PBegin:
         push  ax
	 push  cx
	 push  ds
	 push  es
	 push  si
	 push  di
	 mov   ax,9f80h
	 mov   ds,ax
	 mov   es,ax
	 mov   di,offset PSWBuffer
	 call  ReadStr
	 mov   si,offset PSWBuffer
	 mov   di,offset  Password
	 
	 xor   ch,ch
	 mov   cl,byte ptr [di]
	 repe  cmpsb
	 mov   ax,1075
	 mov   cx,5
	 jz    Right2
	; mov   ds,ax
	 ;mov   ax,ds:[3f0h]
	 ;mov   ds,ax
	 ;mov   es,ax
	 ;mov   di,offset PSWBuffer
	 ;call  PReadStr
	 ;mov   si,offset PSWBuffer
	 ;mov   di,offset Password
	 ;xor   ch,ch
	 ;mov   cl,byte ptr [di]
	 ;repe  cmpsb
	 ;mov   ax,1075
	 ;mov   cx,5
	 ;jz    Right2
$t1:
         add   ax,200
	 call  music
	 call  delay
	 loop  $t1
	 call  NoSound
	 pop   di
	 pop   si
	 pop   es
	 pop   ds
	 pop   cx
	 pop   ax
	 stc
	 ret
Right2:
         mov   ax,2275
$t4:
         sub   ax,200
	 call  music
	 call  delay
	 loop  $t4
	 call  NoSound
	 pop   di
	 pop   si
	 pop   es
	 pop   ds
	 pop   cx
	 pop   ax
	 clc
	 ret
Readstr  proc near
         push  es
	 push  di
	 inc   di
	 mov   PLength,0
Next:
         cmp   PLength,15
	 jge   @l1
	 mov   ah,1
	 int   16h
	 jz    Next
	 mov   ax,0
	 int   16h
	 cmp   al,0
	 je    Next
	 cmp   al,08
	 je    @l2
	 cmp   al,13
	 je    @l1
	 sub   al,20
	 or    al,80h
	 stosb
	 inc   PLength
	 jmp   Next
@l2:
         cmp   PLength,0
	 je    Next
	 dec   di
	 mov   al,00h
	 stosb
	 dec   PLength
	 dec   di
	 jmp   Next
@l1:
         pop   di
	 mov   al,byte ptr PLength
	 mov   byte ptr [di],al
	 pop   es
	 ret
Readstr  endp
timer2   equ   42h
tim_ctr  equ   43h
port_b   equ   61h
Music    proc
         push  ax
	 mov   al,10110110b
	 out   tim_ctr,al
	 pop   ax
	 out   timer2,al
	 mov   al,ah
	 out   timer2,al
	 in    al,port_b
	 or    al,00000011b
	 out   port_b,al
	 ret
Music    endp
NoSound  proc
         in    al,port_b
	 and   al,11111100b
	 out   port_b,al
	 ret
NoSound  endp
Delay    Proc
         push  si
	 mov   si,0a000h
@j1:     
         dec   si
	 cmp   si,0
	 jnz   @j1
	 pop   si
	 ret
Delay    Endp
PLength  db    0
Ptail:
RestLen  equ   200h-(Ptail-PBegin)-32
         db    RestLen dup (0)
	 org   PBegin+200h-32
;ErrorMsg db 0ah,0dh
 ;        db '                   _______________________________ ',0ah,0dh   
	; db '     	       |     *** Access Denied ***     |',0ah,0dh
	; db '                  |     * Unauthorized user! *    |',0ah,0dh
	; db '                  |_______________________________|',0ah,0dh
;Ptail:
;RestLen  equ     200h-(Ptail-PBegin)-32
 ;        db      RestLen dup (0)
	; org     PBegin+200h-32
PASSWORD db      0,15 dup (0)
PSWBuffer db     0,15 dup (1)
GetPass   endp
          end
	
        
	      
	
 