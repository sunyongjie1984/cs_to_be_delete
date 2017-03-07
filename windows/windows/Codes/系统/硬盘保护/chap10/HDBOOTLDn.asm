;hdbootld.asm     ---boot1.asm install program
;masm   hdbootld
;link   hdbootld
;exe2com  hdbootld
;Usage: Before running this program,you must place a floppy in drive a:,
;       and run this program,choose the disk type.
;book: HARDDISK PROTECTION TECHNIQUE HANDBOOK
;page:167
;creat on 02/21/1999
;this program likes fixboot.asm
           .model tiny
	   .code
	   org   100h
start:
       jmp   begin
      
buffer  db  0EBh,29h,90h,48h,6Fh,77h,61h,72h,64h,20h,00h,02h
	db  01h,01h,00h,02h,0E0h,00h,40h,0Bh,0F0h,09h,00h,12h
	db  00h,02h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,0FAh,33h,0C0h,8Eh,0D0h
	db  0BCh,00h,7Ch,8Bh,0F4h,50h,07h,50h,1Fh,0FCh,0BFh,00h
	db  06h,0B9h,00h,01h,0F2h,0A5h,33h,0C0h,50h,0B8h,4Ah,06h
	db  50h,0CBh,0BFh,63h,06h,0E8h,73h,01h,0B8h,01h,02h,0BBh
	db  00h,7Ch,0B9h,01h,00h,0BAh,80h,00h,0CDh,13h,0EAh,00h
	db  7Ch,00h,00h,20h,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,0Dh,0Ah,7Ch,20h
	db  20h,20h,20h,20h,2Ah,2Ah,2Ah,20h,48h,61h,72h,64h
	db  64h,69h,73h,6Bh,20h,62h,6Fh,6Fh,74h,65h,72h,20h
	db  66h,6Ch,6Fh,70h,70h,79h,20h,2Ah,2Ah,2Ah,20h,20h
	db  20h,20h,20h,7Ch,0Dh,0Ah,7Ch,3Dh,3Dh,3Dh,3Dh,3Dh
	db  3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh
	db  3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh
	db  3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,3Dh,7Ch
	db  0Dh,0Ah,7Ch,20h,20h,20h,20h,20h,20h,20h,20h,20h
	db  20h,20h,56h,65h,72h,73h,69h,6Fh,6Eh,20h,31h,2Eh
	db  30h,30h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h
	db  20h,20h,20h,20h,20h,20h,20h,7Ch,0Dh,0Ah,7Ch,20h
	db  20h,20h,20h,54h,68h,69h,73h,20h,64h,69h,73h,6Bh
	db  65h,74h,74h,65h,20h,69h,73h,20h,66h,6Fh,72h,63h
	db  65h,64h,20h,74h,6Fh,20h,62h,6Fh,6Fh,74h,20h,20h
	db  20h,20h,20h,7Ch,0Dh,0Ah,7Ch,20h,20h,20h,20h,66h
	db  72h,6Fh,6Dh,20h,74h,68h,65h,20h,48h,61h,72h,64h
	db  20h,44h,69h,73h,6Bh,2Eh,2Eh,2Eh,20h,20h,20h,20h
	db  20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,7Ch
	db  0Dh,0Ah,7Ch,20h,20h,20h,20h,20h,20h,20h,20h,20h
	db  20h,20h,20h,20h,20h,62h,79h,20h,48h,6Fh,77h,61h
	db  72h,64h,2Ch,20h,30h,32h,2Fh,32h,31h,2Fh,31h,39h
	db  39h,39h,20h,20h,20h,20h,20h,7Ch,0Dh,0Ah,7Ch,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh,5Fh
	db  5Fh,5Fh,5Fh,7Ch,0Dh,0Ah,24h,2Eh,8Ah,05h,3Ch,24h
	db  74h,0Ah,0B4h,0Eh,0BBh,03h,00h,0CDh,10h,47h,0EBh,0EFh
	db  0C3h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
	db  00h,00h,00h,00h,00h,00h,55h,0AAh

;floppy bpb data (get from format.exe )

type1  db   00h,02h,02h,01h,00h,02h,70h,00h,0d0h,02h
       db   0fdh,02h,00h,09h,00h,02h,00h,00h,00h

type2  db   00h,02h,01h,01h,00h,02h,40h,00h,68h,01h
       db   0fch,02h,00h,09h,00h,01h,00h,00h,00h

type3  db   00h,02h,02h,01h,00h,02h,70h,00h,80h,02h
       db   0ffh,01h,00h,08h,00h,02h,00h,00h,00h

type4  db   00h,02h,01h,01h,00h,02h,40h,00h,40h,01h
       db   0feh,01h,00h,08h,00h,01h,00h,00h,00h

type5  db   00h,02h,02h,01h,00h,02h,70h,00h,0a0h,05h
       db   0f9h,03h,00h,09h,00h,02h,00h,00h,00h
       

t_ofs    dw   offset type1
         dw   offset type2
	 dw   offset type3
	 dw   offset type4
	 dw   offset type5

ask_msg  db  ' ________________________________________________',0ah,0dh
         db  '|    *** Hard Disk booter install utility ***    |',0ah,0dh
	 db  '|================================================|',0ah,0dh
	 db  '|   This program is used to install the hard     |',0ah,0dh
	 db  '| disk booter to your floppy...  Howard 02/21/99 |',0ah,0dh
	 db  '|________________________________________________|',0ah,0dh
	 db  '    Do you want to proceed? (y/n)',0ah,0dh,07h,'$'
	 
Media    db  '(1) 360K, (2) 1.2M','$'

suc_msg  db  0dh,0ah,'Hard Disk booter is installed sucessfully!',07h,'$'
err_msg  db  0dh,0ah,'Drive A write error,please check the floppy...',07h,'$'

begin:
       push  cs
       pop   ds
       push  cs
       pop   es
       
       mov   ah,09h
       mov   dx,offset ask_msg
       int   21h
       
echo:
       mov   ah,07h
       int   21h
       cmp   al,'Y'
       je    check_media
       cmp   al,'y'
       je    check_media
       jmp   exit
       
check_media:
       mov   ah,09h
       mov   dx,offset media
       int   21h
p1:
       mov   ah,07h
       int   21h
       cmp   al,'1'
       je    dtype1
       cmp   al,'2'
       je    install

       jmp   p1
       
dtype1:   
       mov   si,[word ptr t_ofs]
       mov   di,offset buffer+11
       mov   cx,19
       rep   movsb

       

       
install:
       mov   si,5
       push  cs
       pop   es
       
writeboot:
       push  si
       mov   ax,0301h
       mov   bx,offset buffer
       mov   cx,0001h
       mov   dx,0
       int   13h
       pop   si
       jnc   sucess
       dec   si
       jnz   writeboot
       
error:
;       call  checket
       mov   ah,09h
       mov   dx,offset err_msg
       int   21h
       jmp   exit
       
sucess:
;       call  checket
       mov   ah,09h
       mov   dx,offset suc_msg
       int   21h
       
exit:
       mov   ah,4ch
       int   21h
       end  start
       
	 