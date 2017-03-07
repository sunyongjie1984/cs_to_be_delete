;<<硬盘保护技术手册>> page 117
;编码程序 encode.asm

       .MODEL tiny
       .CODE
       org   100h
begin:
      push   cs
      pop    ds
      push   cs
      pop    es
      mov    ax,0201h
      mov    bx,offset Buffer
      mov    cx,0001h
      mov    dx,0080h
      int    13h
      mov    si,offset Buffer+1BEh
      mov    cx,20h
mask1:
      xor  word ptr[si],0AAAAh
      inc  si
      inc  si
      loop mask1
      mov  ax,0301h
      mov  bx,offset Buffer
      mov  cx,0001h
      mov  dx,0080h
      int  13h
      mov  ah,4ch
      int 21h
Buffer db   512 dup(0)
       END begin