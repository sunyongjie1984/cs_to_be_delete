/***************************************************/
*       File Name:MBR.C                            *
****************************************************/
#include <bios.h>
#include <ctype.h>
main()
{
 int i,k,result;
 int line=1,charcount=0;
 unsigned char buffer[512];
 char c[17];
 c[16]='\0';
 result=biosdisk(2,0x80,0,0,1,1,buffer);
 clrscr();
 if(!result)
 {printf("%-7d",line);
  for(i=0;i<512;i++)
   {printf("%02x",buffer[i]);
    charcount+=1;
    k=i%16;
    if(isprint(buffer[i]))
    c[k]=buffer[i];
    else
    c[k]=".";
    if(charcount==16)
    {printf("           ");
     charcount=0;
     printf("%s\n",c);
     line++;
     if(i==255)getch();
     if(i!=511)printf("%-7d",line);
    }
   }
   else
   printf("Read Partition Table Error!");
}
