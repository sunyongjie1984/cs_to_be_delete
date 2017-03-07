;find int 13h old address port
;int13adr.asm--driver interrupt trace program
;<<handbook for harddisk protect technology>> page 272
;Use trace to old driver interrupt address port
;tasm int13adr.asm
;tlink /t int13adr.asm
      .MODEL tiny
      .CODE
      org    100h
begin:
         push  cs
	 pop   ds
	 mov   ax,3513h
	 int   21h
	 mov   int13_seg,es
	 mov   int13_ofs,bx
	 mov   dx,offset int1_hndlr
	 mov   ax,2501h
	 int   21h
	 pushf
	 pop   ax
	 or    ax,0100h
	 push  ax
	 popf
	 mov   ah,0
	 mov   dl,80h
	 pushf
	 call  dword ptr int13_hndlr
	 mov   ah,4ch
	 int   21h
int13_hndlr    label dword
int13_ofs      dw ?
int13_seg      dw ?
print_char     proc near
         mov   ah,0eh
	 int   10h
	 ret
print_char     endp
hextable       db '0123456789ABCDEF'
print_hex      proc near
         push  ax
	 push  bx
	 push  dx
	 shr   dl,1
	 shr   dl,1
	 shr   dl,1
	 shr   dl,1
	 xor   bx,bx
	 mov   bl,dl
	 mov   al,hextable[bx]
	 call  print_char
	 pop   dx
	 push  dx
	 and   dl,0fh
	 xor   bx,bx
	 mov   bl,dl
	 mov   al,hextable[bx]
	 call  print_char
	 pop   dx
	 pop   bx
	 pop   ax
	 ret
print_hex      endp
print_word     proc near
         xchg  dh,dl
	 call  print_hex
	 xchg  dh,dl
	 call  print_hex
	 ret
print_word     endp
int1_hndlr:
         push  bp
	 mov   bp,sp
	 push  dx
	 mov   dx,word ptr [bp+0004]
	 cmp   dx,0f000h
	 je    print
	 jmp   exit
print:
         mov   cs:int13_seg,dx
	 call  print_word
	 mov   dx,word ptr [bp+0002]
	 mov   cs:int13_ofs,dx
	 call  print_word
	 and   word ptr [bp+0006],0feffh
	 jmp   exit1
exit:
         or    word ptr [bp+0006],0100h
exit1:
         pop   dx
	 pop   bp
	 iret
	 end begin
	 
	 