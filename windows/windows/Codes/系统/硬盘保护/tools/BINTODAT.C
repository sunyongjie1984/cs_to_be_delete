/* 把二进制文件转换成汇编语言的数据文件格式 */
/* bintodat *.bin *.out */
/* 《硬盘保护技术手册》page 291 */


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
int main(int argc,char * *argv)
{
 FILE *fp1,*fp2;
 long fsize;
 unsigned i;
 unsigned char tmp;
 if(argc<2)
 {
  printf("Usage:BINTODAT [input] [output]");
  exit(1);
 }
 fp1=fopen(argv[1],"rb");
  if(fp1==NULL)
  {printf("Open file %s error ",argv[1]);
   exit(0);
  }
 fp2=fopen(argv[2],"wt");
 fsize=filesize(fp1);
 fprintf(fp2,"\n\tdb  ");
 for(i=0;i<fsize;i++)
 {
  tmp=fgetc(fp1);
  if(tmp<0xa0)
   fprintf(fp2,"%02Xh,",tmp);
  else
   fprintf(fp2,"%03Xh,",tmp);
  if((i+1)%12==0)fprintf(fp2,"\n\tdb  ");
 }
 printf("Process O.K.");
 return 0;
}
