;xbootld.asm
;tasm xbootld
;tasm /t xbootld
;page 94
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
	 mov   cx,0100h
	 repne movsw
	 mov   ax,0301h
	 mov   bx,offset Sector
	 mov   cx,0001h
	 mov   dx,0080h
	 int   13h
	 mov   ah,4ch
	 int   21h
Buffer   db    512 dup (0)
   
Sector	db  0FAh,33h,0C0h,8Eh,0D0h,0BCh,00h,7Ch,8Bh,0F4h,50h,07h
	db  50h,1Fh,0FBh,0FCh,0BFh,00h,06h,0B9h,00h,01h,0F2h,0A5h
	db  0EAh,1Dh,06h,00h,00h,0B8h,01h,02h,0BBh,00h,08h,0B9h
	db  01h,00h,0BAh,80h,00h,0CDh,13h,0BFh,00h,06h,0BEh,00h
	db  08h,0B9h,00h,01h,0FCh,0F3h,0A7h,74h,14h,0BEh,17h,07h
	db  0E8h,2Fh,01h,0B8h,01h,03h,0BBh,00h,06h,0B9h,01h,00h
	db  0BAh,80h,00h,0CDh,13h,0BEh,0BEh,07h,0B3h,04h,80h,3Ch
	db  80h,74h,0Eh,80h,3Ch,00h,75h,1Ch,83h,0C6h,10h,0FEh
	db  0CBh,75h,0EFh,0CDh,18h,8Bh,14h,8Bh,4Ch,02h,8Bh,0EEh
	db  83h,0C6h,10h,0FEh,0CBh,74h,0Dh,80h,3Ch,00h,74h,0F4h
	db  0BEh,0AEh,06h,0E8h,0F0h,00h,0EBh,0FEh,0BFh,05h,00h,0BBh
	db  00h,7Ch,0B8h,01h,02h,57h,0CDh,13h,5Fh,73h,0Ch,33h
	db  0C0h,0CDh,13h,4Fh,75h,0EDh,0BEh,0D2h,06h,0EBh,0E0h,0BEh
	db  0F7h,06h,0BFh,0FEh,7Dh,81h,3Dh,55h,0AAh,75h,0D4h,8Bh
	db  0F5h,0EAh,00h,7Ch,00h,00h,49h,6Eh,76h,61h,6Ch,69h
	db  64h,20h,70h,61h,72h,74h,69h,74h,69h,6Fh,6Eh,20h
	db  74h,61h,62h,6Ch,65h,2Eh,20h,4Fh,68h,2Ch,6Dh,79h
	db  20h,67h,6Fh,64h,21h,00h,45h,72h,72h,6Fh,72h,20h
	db  6Ch,6Fh,61h,64h,69h,6Eh,67h,20h,6Fh,70h,65h,72h
	db  61h,74h,69h,6Eh,67h,20h,73h,79h,73h,74h,65h,6Dh
	db  2Eh,20h,57h,68h,79h,3Fh,00h,4Dh,69h,73h,73h,69h
	db  6Eh,67h,20h,6Fh,70h,65h,72h,61h,74h,69h,6Eh,67h
	db  20h,73h,79h,73h,74h,65h,6Dh,2Eh,20h,53h,68h,69h
	db  74h,21h,00h,4Dh,61h,73h,74h,65h,72h,20h,42h,6Fh
	db  6Fh,74h,20h,53h,65h,63h,74h,6Fh,72h,20h,63h,68h
	db  61h,6Eh,67h,65h,64h,2Eh,0Ah,0Dh,44h,6Fh,6Eh,27h
	db  74h,20h,77h,6Fh,72h,72h,79h,2Ch,49h,20h,68h,61h
	db  76h,65h,20h,72h,65h,63h,6Fh,76h,65h,72h,65h,64h
	db  20h,69h,74h,21h,20h,43h,6Ch,65h,76h,65h,72h,21h
	db  20h,45h,54h,2Dh,4Dh,6Fh,75h,73h,65h,20h,59h,65h
	db  61h,68h,21h,0Ah,0Dh,00h,0ACh,3Ch,00h,74h,0Bh,56h
	db  0BBh,07h,00h,0B4h,0Eh,0CDh,10h,5Eh,0EBh,0F0h,0C3h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
        db  00h, 00h, 80h, 01h, 01h, 00h, 0bh, 0feh, 3fh, 79h, 3fh, 00h
        db  00h, 00h, 0bbh, 0e7h, 1dh, 00h, 00h, 00h, 01h, 7ah, 82h, 0feh
        db  3fh, 80h, 0fah, 0e7h, 1dh, 00h, 47h, 0b7h, 01h, 00h, 00h, 00h 
        db  01h, 81h, 83h, 0feh, 3fh, 0e6h, 41h, 9fh, 1fh, 00h, 0e6h, 00h 
        db  19h, 00h, 00h, 00h, 01h, 0e7h, 0fh, 0feh, 0bfh, 0bh, 27h, 0a0h 
        db  38h, 00h, 0a6h,11h, 48h, 00h, 55h, 0aah


       end begin