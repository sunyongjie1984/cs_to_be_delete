;xbootld.asm
;tasm xbootld
;tasm /t xbootld
;page 105
         .MODEL tiny
	 .CODE
	 org    100h
begin:
         push  cs
	 pop   ds
	 push  cs
	 pop   es
	 mov   ax,0201h
	 mov   bx,offset Buffer
	 mov   cx,0001h
	 mov   dx,0080h
	 int   13h
	 cld
	 mov   si,offset Buffer+01BEh
	 mov   di,offset Sector+01BEh
	 mov   cx,21h
	 repne movsw
	 mov   ax,0301h
	 mov   bx,offset Sector
	 mov   cx,0001h
	 mov   dx,0080h
         pushf
	 call  dword ptr int13_hndlr
	 mov   ah,4ch
	 int   21h

int13_hndlr    label dword
int13_ofs      dw    09ae4h
int13_seg      dw    0f000h

Buffer   db    512 dup (0)
   
Sector	db  0FAh,33h,0C0h,8Eh,0D0h,0BCh,00h,7Ch,8Bh,0F4h,50h,07h
	db  50h,1Fh,0FBh,0FCh,0BFh,00h,06h,0B9h,00h,01h,0F2h,0A5h
	db  0EAh,1Dh,06h,00h,00h,0Eh,1Fh,0Eh,07h,0B8h,01h,02h
	db  0BBh,00h,08h,0B9h,01h,00h,0BAh,80h,00h,9Ch,0FFh,1Eh
	db  89h,07h,0BFh,00h,06h,0BEh,00h,08h,0B9h,00h,01h,0FCh
	db  0F3h,0A7h,74h,17h,0BEh,21h,07h,0E8h,32h,01h,0B8h,01h
	db  03h,0BBh,00h,06h,0B9h,01h,00h,0BAh,80h,00h,9Ch,0FFh
	db  1Eh,89h,07h,0BEh,0BEh,07h,0B3h,04h,80h,3Ch,80h,74h
	db  0Eh,80h,3Ch,00h,75h,1Ch,83h,0C6h,10h,0FEh,0CBh,75h
	db  0EFh,0CDh,18h,8Bh,14h,8Bh,4Ch,02h,8Bh,0EEh,83h,0C6h
	db  10h,0FEh,0CBh,74h,0Dh,80h,3Ch,00h,74h,0F4h,0BEh,0B8h
	db  06h,0E8h,0F0h,00h,0EBh,0FEh,0BFh,05h,00h,0BBh,00h,7Ch
	db  0B8h,01h,02h,57h,0CDh,13h,5Fh,73h,0Ch,33h,0C0h,0CDh
	db  13h,4Fh,75h,0EDh,0BEh,0DCh,06h,0EBh,0E0h,0BEh,01h,07h
	db  0BFh,0FEh,7Dh,81h,3Dh,55h,0AAh,75h,0D4h,8Bh,0F5h,0EAh
	db  00h,7Ch,00h,00h,49h,6Eh,76h,61h,6Ch,69h,64h,20h
	db  70h,61h,72h,74h,69h,74h,69h,6Fh,6Eh,20h,74h,61h
	db  62h,6Ch,65h,2Eh,20h,4Fh,68h,2Ch,6Dh,79h,20h,67h
	db  6Fh,64h,21h,00h,45h,72h,72h,6Fh,72h,20h,6Ch,6Fh
	db  61h,64h,69h,6Eh,67h,20h,6Fh,70h,65h,72h,61h,74h
	db  69h,6Eh,67h,20h,73h,79h,73h,74h,65h,6Dh,2Eh,20h
	db  57h,68h,79h,3Fh,00h,4Dh,69h,73h,73h,69h,6Eh,67h
	db  20h,6Fh,70h,65h,72h,61h,74h,69h,6Eh,67h,20h,73h
	db  79h,73h,74h,65h,6Dh,2Eh,20h,53h,68h,69h,74h,21h
	db  00h,4Dh,61h,73h,74h,65h,72h,20h,42h,6Fh,6Fh,74h
	db  20h,53h,65h,63h,74h,6Fh,72h,20h,63h,68h,61h,6Eh
	db  67h,65h,64h,2Eh,0Ah,0Dh,44h,6Fh,6Eh,27h,74h,20h
	db  77h,6Fh,72h,72h,79h,2Ch,49h,20h,68h,61h,76h,65h
	db  20h,72h,65h,63h,6Fh,76h,65h,72h,65h,64h,20h,69h
	db  74h,21h,20h,43h,6Ch,65h,76h,65h,72h,21h,20h,45h
	db  54h,2Dh,4Dh,6Fh,75h,73h,65h,20h,59h,65h,61h,68h
	db  21h,0Ah,0Dh,00h,0ACh,3Ch,00h,74h,0Bh,56h,0BBh,07h
	db  00h,0B4h,0Eh,0CDh,10h,5Eh,0EBh,0F0h,0C3h,0E4h,9Ah,00h
	db  0F0h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,80h,01h,01h,00h,0Bh,0FEh,3Fh,79h,3Fh,00h
	db  00h,00h,0BBh,0E7h,1Dh,00h,00h,00h,01h,7Ah,82h,0FEh
	db  3Fh,80h,0FAh,0E7h,1Dh,00h,47h,0B7h,01h,00h,00h,00h
	db  01h,81h,83h,0FEh,3Fh,0E6h,41h,9Fh,1Fh,00h,0E6h,00h
	db  19h,00h,00h,00h,01h,0E7h,0Fh,0FEh,0BFh,0Bh,27h,0A0h
	db  38h,00h,0A6h,11h,48h,00h,55h,0AAh
       end begin