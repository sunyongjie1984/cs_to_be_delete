/* cencode.c    encode.asm C version */
/* tc20 pass */
/* HARDDISK PROTECTION TECHNIQUE HANDBOOK */
/* PAGE 127 WRITE ON 02/20/1999 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <sys\stat.h>
#include <fcntl.h>

char buffer[512];
void title()
{
 puts("\n __________________________________________");
 puts("|     *** C-Xlock install program ***      |");
 puts("|------------------------------------------|");
 puts("|    -- By Stephen Howard   on 02/13/1999  |");
 puts("|__________________________________________|");
}

main()
{
 int i;
 title();
 while((biosdisk(0x02,0x80,0,0,1,1,buffer))!=0);
 for(i=0;i<0x40;i++)
    *(buffer+0x1be+i)^=0xaa;
 while((biosdisk(0x03,0x80,0,0,1,1,buffer))!=0);
 puts("\nEncode OK!");
}