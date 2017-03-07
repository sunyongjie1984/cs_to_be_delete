
#include "dos.h"
#include "stdio.h"
unsigned char buf[128];
FILE *fp;
void readcmos()
{
 int i;
 for(i=0;i<128;i++)
 {outportb(0x70,i);
  buf[i]=inportb(0x71);
 }
}
void writecmos()
{
 int i;
 for(i=0;i<128;i++)
 {outportb(0x70,i);
  outportb(0x71,buf[i]);
 }
}
void openfile(char *c)
{
if((fp=fopen("cmos.dat",c))==NULL)
 {
 clrscr();
 gotoxy(20,15);
 printf("File open error!\n");
 fclose(fp);
 exit(0);
 }
}
void success()
{
 gotoxy(20,22);
 printf("Success!Please hit any key...");
 getch();
}
void savecmos()
{
 int size;
 openfile("wb");
 readcmos();
 size=fwrite(buf,128,1,fp);
 if(size!=1)
  {clrscr();
   gotoxy(20,15);
   printf("Save data error!\n");
   fclose(fp);
   exit(0);
  }
 fprintf(fp,"\n");
 fclose(fp);
 success();
}
void restallcmos()
{
 int size;
 openfile("rb");
 size=fread(buf,128,1,fp);
 if(size!=1)
 {clrscr();
  gotoxy(20,15);
  printf("Read data error!\n");
  fclose(fp);
  exit(0);
  }
 writecmos();
 fclose(fp);
 success();
}
void checkcmos()
{
 unsigned char bufl[128];
 int i;
 openfile("rb");
 readcmos();
 fread(bufl,128,1,fp);
 for(i=10 ;i<128;i++)
 {if (buf[i]!=bufl[i]) break;}
 if(i!=128)
  {gotoxy(20,22);
   printf("Data change in cmos!Please hit any key...");
   getch();
   exit(0);
  }
 gotoxy(20,22);
 printf("All right!Please hit any key...");
 getch();
}
void opencmos()
{
 outportb(0x70,0x11);
 outportb(0x71,0xff);
 success();
}
main()
{
 int key=0;
 while(key!=5)
 {clrscr();
  gotoxy(20,13);printf("1--Save Cmos\n");
  gotoxy(20,14);printf("2--Restall Cmos\n");
  gotoxy(20,15);printf("3--Check Cmos\n");
  gotoxy(20,16);printf("4--Open Cmos\n");
  gotoxy(20,17);printf("5--Exit\n");
  gotoxy(20,19);printf("Please choose(1-5):");
  gotoxy(39,19);key=getch()-48;
  switch(key)
  {case 1:savecmos();break;
   case 2:restallcmos();break;
   case 3:checkcmos();break;
   case 4:opencmos();
  }
 }
clrscr();
}