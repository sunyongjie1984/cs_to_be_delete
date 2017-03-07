;mbootld.asm     mboot.asm install program
;tasm mbootld.
;tlink /t mbootld
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;PAGE 154
;CREAT ON 02/21/1999

      .MODEL TINY
      .code
      org    100h
begin:
      push   cs
      pop    ds
      push   cs
      pop    es
      mov    ax,0201h
      mov    bx,offset buffer
      mov    cx,0001h
      mov    dx,0080h
      int   13h
      cld
      mov   si,offset buffer+01beh
      mov   di,offset sector+01beh
      mov   cx,20h
      repne movsw
      mov   ax,0301h
      mov   bx,offset sector
      mov   cx,0001h
      mov   dx,0080h
      int   13h
      mov   ah,4ch
      int   21h

buffer     db   512 dup(0)
sector  db  0FAh,33h,0C0h,8Eh,0D0h,0BCh,00h,7Ch,8Bh,0F4h,50h,07h
	db  50h,1Fh,0FBh,0FCh,0BFh,00h,06h,0B8h,00h,01h,0F3h,0A5h
	db  0B8h,1Dh,06h,50h,0C3h,0C6h,06h,0BEh,07h,00h,0C6h,06h
	db  0CEh,07h,00h,0C6h,06h,0DEh,07h,00h,0C6h,06h,0EEh,07h
	db  00h,0BEh,0Ah,07h,0E8h,49h,01h,0B0h,20h,0B1h,01h,0B4h
	db  0Ah,0CDh,0Ah,0B4h,00h,0CDh,16h,24h,5Fh,50h,0B4h,0Ah
	db  0B9h,01h,00h,0CDh,10h,58h,3Ch,57h,74h,06h,3Ch,4Ch
	db  74h,09h,0EBh,0D9h,0B0h,06h,0BEh,74h,07h,0EBh,05h,0B0h
	db  02h,0BEh,7Bh,07h,0BFh,6Dh,07h,0B9h,06h,00h,0FCh,0F3h
	db  0A4h,0B3h,04h,0BEh,0BEh,07h,38h,44h,04h,74h,0Fh,83h
	db  0C6h,10h,0FEh,0CBh,75h,0F4h,0BEh,60h,07h,0E8h,0FCh,00h
	db  0EBh,0FEh,0C6h,04h,80h,56h,53h,0B8h,01h,03h,0BBh,00h
	db  06h,0B9h,01h,00h,0BAh,80h,00h,0CDh,13h,5Bh,5Eh,8Bh
	db  14h,8Bh,4Ch,02h,8Bh,0EEh,0BFh,05h,00h,0BBh,00h,7Ch
	db  0B8h,01h,02h,0CDh,13h,73h,0Fh,33h,0C0h,0CDh,13h,4Fh
	db  75h,0EFh,0BEh,0D0h,06h,0E8h,0C4h,00h,0EBh,0FEh,0BEh,0F0h
	db  06h,81h,3Eh,0FEh,7Dh,55h,0AAh,75h,0F0h,8Bh,0F5h,0B8h
	db  00h,7Ch,50h,0C3h,1Fh,45h,72h,72h,6Fh,72h,20h,6Ch
	db  6Fh,61h,64h,69h,6Eh,67h,20h,6Fh,70h,65h,72h,61h
	db  74h,69h,6Eh,67h,20h,73h,79h,73h,74h,65h,6Dh,21h
	db  19h,4Dh,69h,73h,73h,69h,6Eh,67h,20h,6Fh,70h,65h
	db  72h,61h,74h,69h,6Eh,67h,20h,73h,79h,73h,74h,65h
	db  6Dh,21h,55h,28h,43h,29h,6Fh,70h,79h,72h,69h,67h
	db  68h,74h,20h,48h,6Fh,77h,61h,72h,64h,20h,44h,72h
	db  65h,61h,6Dh,2Dh,6Ch,69h,76h,65h,73h,2Eh,0Dh,0Ah
	db  4Dh,75h,6Ch,74h,69h,4Fh,53h,20h,4Dh,61h,73h,74h
	db  65h,72h,20h,62h,6Fh,6Fh,74h,20h,70h,72h,6Fh,67h
	db  72h,61h,6Dh,0Dh,0Ah,49h,6Eh,70h,75h,74h,20h,4Ch
	db  3Dh,4Ch,69h,6Eh,75h,78h,2Ch,57h,3Dh,57h,69h,6Eh
	db  64h,6Fh,77h,73h,13h,43h,61h,6Eh,6Eh,6Fh,74h,20h
	db  66h,69h,6Eh,64h,20h,78h,78h,78h,78h,78h,78h,78h
	db  57h,69h,6Eh,64h,6Fh,77h,73h,4Ch,69h,6Eh,75h,78h
	db  0B7h,00h,0B4h,03h,0CDh,10h,32h,0EDh,0ACh,8Ah,0C8h,0BBh
	db  09h,00h,0B8h,01h,13h,8Bh,0EEh,0CDh,10h,0C3h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,55h,0AAh


end begin
      