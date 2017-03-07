/*backup Hardisk partition table */
#include <bios.h>
#include <dos.h>
static char *name={"PARTNSAV.FIL"};
main(int argc,char *argv[])
{int cmd;
 char *fname={" "},buf[513],*fo={""};
 FILE *fp;

 printf("\nFile Partition Tabel Mirror Utility Version 2.00");
 printf("\n\t(C) ETMouseSoft Made by ETMouse 1998.10\n");
 if(argc!=3)
 {printf("\a\nUsage:\n\tPARTN /R[/r] d:");
  printf("Copy the HardDisk's Partition tabel to a drive(d:).\n");
  printf("\tPARTN /W[/w] D:");
  printf("Rebuild the HardDisk's Partition Tabel from a drive(d:).\n");
  exit (1);
 }
  if(!stricmp(argv[1],"/r")){cmd=2;fo="wb";} else
  if(!stricmp(argv[1],"/w")){cmd=3;fo="rb";} else
   {printf("\a\nIllegal command %s",argv[1]);
    exit (1);
   }
strncpy(fname,argv[2],2);
if((tolower(fname[0])>='a'||tolower(fname[0]<='d') && fname[1]==':'))
  strcat(fname,name);
  else
   {printf("\a\nBad drive %s !\n",fname);
    exit(1);
   }
if((fp=fopen(fname,fo))==NULL)
   {printf("\a\nUnable to open %s",fname);
    exit(1);
   }
   if(cmd==3)
   {fseek(fp,27L,SEEK_SET);
    fread(buf,sizeof(char),512,fp);}
    if(biosdisk(cmd,0x80,0,0,1,1,buf))
     {printf("\nPartition Tabel operate error!");
      exit(1);
     }
    if(cmd==2)
    {
     fputs("=>Partition tabel's copy <=",fp);
     fwrite(buf,sizeof(char),512,fp);}
     if(fclose(fp))
     {printf("\a\nUnable to close %s",fname);
      exit(1);
     }
     printf("\nSuccess!");
 }