;tblockld.asm --hotkey harddisk lock and hdpt hidden load program
;tasm tblockld.asm
;tlink /t tblockld.asm
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;PAGE 121
;WRITE ON 2/20/1999
;MODIFI ON 2/20/1999
        .model tiny
	.code
	org    100h
begin:
        push  cs
	pop   ds
	push  cs
	pop   es
	mov   ax,0200h
	mov   bx,offset buffer
	mov   cx,0001h
	mov   dx,0080h
	int   13h
	cld
	mov   si,offset buffer+01beh
	mov   di,offset sector+01beh
	mov   cx,0100h
	repne movsw
;	mov   ax,0301h
	;mov   bx,offset sector
	;mov   cx,0001h
	;mov   dx,0080h
	;int   13h
	;mov   ah,4ch
	;int   21h
	mov   si,offset sector+01beh
	mov   cx,20h
mask1:
	xor   word ptr [si],0aaaah
	inc   si
	inc   si
	loop  mask1
	mov   ax,0301h
	mov   bx,offset sector
	mov   cx,0001h
	mov   dx,0080h
	int   13h
	mov   ah,4ch
	int   21h
buffer   db   512 dup(0)
sector  db  0FAh,33h,0C0h,8Eh,0D0h,0BCh,00h,7Ch,8Bh,0F4h,50h,07h
	db  50h,1Fh,0FBh,0FCh,0BFh,00h,06h,0B9h,00h,01h,0F2h,0A5h
	db  0EAh,1Dh,06h,00h,00h,0BEh,0E8h,06h,0E8h,0F5h,00h,0B4h
	db  00h,0CDh,16h,80h,0FCh,52h,74h,08h,0BEh,05h,07h,0E8h
	db  0E6h,00h,0EBh,0FEh,0BEh,0BEh,07h,0B3h,04h,80h,3Ch,80h
	db  74h,0Eh,80h,3Ch,00h,75h,1Ch,83h,0C6h,10h,0FEh,0CBh
	db  75h,0EFh,0CDh,18h,8Bh,14h,8Bh,4Ch,02h,8Bh,0EEh,83h
	db  0C6h,10h,0FEh,0CBh,74h,0Dh,80h,3Ch,00h,74h,0F4h,0BEh
	db  95h,06h,0E8h,0B3h,00h,0EBh,0FEh,0BFh,05h,00h,0BBh,00h
	db  7Ch,0B8h,01h,02h,57h,0CDh,13h,5Fh,73h,0Ch,33h,0C0h
	db  0CDh,13h,4Fh,75h,0EDh,0BEh,0AEh,06h,0EBh,0E0h,0BEh,0CEh
	db  06h,0BFh,0FEh,7Dh,81h,3Dh,55h,0AAh,75h,0D4h,8Bh,0F5h
	db  0EAh,00h,7Ch,00h,00h,49h,6Eh,76h,61h,6Ch,69h,64h
	db  20h,70h,61h,72h,74h,69h,74h,69h,6Fh,6Eh,20h,74h
	db  61h,62h,6Ch,65h,21h,00h,45h,72h,72h,6Fh,72h,20h
	db  6Ch,6Fh,61h,64h,69h,6Eh,67h,20h,6Fh,70h,65h,72h
	db  61h,74h,69h,6Eh,67h,20h,73h,79h,73h,74h,65h,6Dh
	db  21h,00h,4Dh,69h,73h,73h,69h,6Eh,67h,20h,6Fh,70h
	db  65h,72h,61h,74h,69h,6Eh,67h,20h,73h,79h,73h,74h
	db  65h,6Dh,21h,00h,50h,72h,65h,73h,73h,20h,70h,61h
	db  73h,73h,6Bh,65h,79h,20h,74h,6Fh,20h,63h,6Fh,6Eh
	db  74h,69h,6Eh,75h,65h,3Ah,0Ah,0Dh,00h,55h,6Eh,61h
	db  75h,74h,68h,6Fh,72h,69h,7Ah,65h,64h,20h,55h,73h
	db  65h,72h,21h,00h,0ACh,3Ch,00h,74h,0Bh,56h,0BBh,07h
	db  00h,0B4h,0Eh,0CDh,10h,5Eh,0EBh,0F0h,0C3h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
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
	
