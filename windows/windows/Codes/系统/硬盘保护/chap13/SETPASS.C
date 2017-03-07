/* setpass.c <<Handbook for HardDisk Protect technology>> Page229 */
#include <stdio.h>
#include <dos.h>
#define MemSize *(unsigned far *)0x00400013

void ReadStr(char *str)
    {
     unsigned char Plength=1;
     unsigned xx,yy,x;
     union REGS r;
     xx=wherex();
     yy=wherey();
     x=xx;
     do
       {
	gotoxy(xx,yy);
	r.h.ah=0;
	int86(0x16,&r,&r);
	if ((r.h.ah!=28)&&(r.h.ah!=14)&&(r.h.ah!=1))
	  {
	   *(str+Plength)=(r.h.ah-20)|0x80;
	   gotoxy(xx,yy);
	   putch('*');
	   xx++;
	   Plength++;
	  }
	else if (r.h.ah==14)
	       {xx--;
		if(xx<x) xx=x;
		gotoxy(xx,yy);
		putch(' ');
		if(Plength>1) Plength--;
	       }
	 else if(r.h.ah==1) Plength=0;
       }while((r.h.ah!=28)&&(r.h.ah!=1)&&(Plength<15));
       *(str+0)=Plength-1;
     }
 int CheckPass(char *src,char *dest)
    {
     unsigned char Plength;
     Plength=*(src+0);
     while (Plength>0)
	  {
	   if(*(src+Plength)!=*(dest+Plength))
	     return -1;
	   Plength--;
	  }
    return 1;
   }
 int CopyPass(char *scr,char *dest)
    {
     char Plength;
     Plength=*(scr+0);
     while (Plength>=0)
	  {
	   *(dest+Plength)=*(scr+Plength);
	   Plength--;
	  }
    }
 void title()
 {
  puts("\n\t_________________________________________________");
  puts("\t|     *** HD Anti-Virus & Security System ***     |");
  puts("\t|-------------------------------------------------|");
  puts("\t|                ET-Mouse Dream WorkShop    1998  |");
  puts("\t|_________________________________________________|");
 }
 void reboot(void)
     {
      void (far *reboot_ptr)(void);
      unsigned int far *i_ptr;
      clrscr();
      i_ptr=MK_FP(0x0040,0x0072);
      *i_ptr=0x1234;
      reboot_ptr=MK_FP(0xf000,0xfffe);
      reboot_ptr();
     }
 int ReadPass(char *buffer)
    {
     union REGS ireg;
     struct SREGS oreg;
     ireg.x.ax=0x0201;
     ireg.x.bx=FP_OFF(buffer);
     ireg.x.cx=0x0006;
     ireg.x.dx=0x0080;
     oreg.es=FP_SEG(buffer);
     int86x(0x50,&ireg,&ireg,&oreg);
     return ireg.h.ah;
    }
 int WritePass(char *buffer)
    {
     union REGS ireg;
     struct SREGS oreg;
     ireg.x.ax=0x0301;
     ireg.x.bx=FP_OFF(buffer);
     ireg.x.cx=0x0006;
     ireg.x.dx=0x0080;
     oreg.es=FP_SEG(buffer);
     int86x(0x50,&ireg,&ireg,&oreg);
     return ireg.h.ah;
    }
 void main()
     {
      char buffer[512];
      char passwd[16],passwd1[16];
      char *source;
      char key;
      if (MemSize==0x280)
	{
	 puts("\nHardDisk Lock Not Insalled!");
	 putch(0x07);
	 exit(1);
	}
      title();
      while(ReadPass(buffer)!=0)
	 source=buffer+0x200-32;
      printf("\nOld Password:");
      ReadStr(passwd);
      if (CheckPass(source,passwd)==1)
	{
	 printf("\nNew Password:");
	 ReadStr(passwd);
	 printf("\nVerify:");
	 ReadStr(passwd1);
	 if (CheckPass(passwd,passwd1)==1)
	   {
	    CopyPass(passwd,source);
	    WritePass(buffer);
	    printf("\nDo you want to reboot to enable new password?(Y\N)");

	    key=getchar();
	    if((key=='Y')||(key=='y'))
	     reboot();
	   }
	  else
	   {
	    printf("\nPassword Verify Error!");
	    exit(1);
	   }
	 }
       else
	 {
	  puts("\nWrong Password!");
	  exit (1);
	 }
     }

