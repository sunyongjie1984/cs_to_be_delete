/* 把二进制文件转换成C语言的数据文件格式 */
/* bintocat *.bin *.out */
/* 《硬盘保护技术手册》page 293 */

#include <stdio.h>
#include <stdlib.h>
long filesize(FILE *stream)
{
 long curpos,length;
 curpos=ftell(stream);
 fseek(stream,0L,SEEK_END);
 length=ftell(stream);
 fseek(stream,curpos,SEEK_SET);
 return length;
}
int main(int argc,char * * argv)
{
 FILE *fp1,*fp2;
 long fsize;
 unsigned i;
 unsigned char tmp;
 if (argc<2)
 {printf("Usage:BINTOCAT [input][output]");
  exit(1);
 }
 fp1=fopen(argv[1],"rb");
 if(fp1==NULL)
  {printf("Open file %s error",argv[1]);
   exit(1);
  }
 fp2=fopen(argv[2],"wt");
 fsize=filesize(fp1);
 fprintf(fp2,"\n{");
 for(i=0;i<fsize;i++)
 {tmp=fgetc(fp1);
  fprintf(fp2,"0x%02X,",tmp);
  if((i+1)%12==0)fprintf(fp2,"\n\t");
 }
 fprintf(fp2,"}");
 printf("Process O.K.");
 return 0;
}