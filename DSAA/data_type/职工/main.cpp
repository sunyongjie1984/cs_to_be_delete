/*【要求】 
职工信息包括职工号，姓名，性别，年龄，学历，工资，住址，电话等（职工号不相等）。试设计一职工信息管理系统，使之能够提供下列功能： 
（1）系统以菜单方式工作 
（2）职工信息录入功能（职工信息用文件保存） 
（3）职工信息浏览功能 
（4）职工信息查询功能，查询方式： 
1）按学历查询 
2）按职工号查询 
（5）职工信息删除，修改功能（可选项）。 




*/
#include <iostream>
#include <string>
using namespace std; 
void menu() 
{ 
int n,w1; 
do 
{ 
printf("\t\t************************************************\n\n"); 
printf("\t\t************************************************\n\n"); 

printf("\t\t *** choose function ************\n\n"); 
printf("\t\t *** 1 Enter new data ************\n\n"); 
printf("\t\t *** 2 Modify data ************\n\n"); 
printf("\t\t *** 3 Search by people.xueli and num*****\n\n"); 
printf("\t\t *** 4 Browse data ************\n\n"); 
printf("\t\t *** 5 add data ************\n\n"); 
printf("\t\t *** 6 Exit ************\n\n"); 
printf("\t\t************************************************\n\n"); 
printf("\t\t************************************************\n\n"); 
printf("Choose your number(1-6):[ ]\b\b"); 
scanf("%d",&n); 
if(n<1||n>6) 
w1=1; 
else w1=0; 
} 
while(w1==1); 
switch(n) 
{ 
case 1:enter();break; 
case 2:modify();break; 
case 3:search();break; 
case 4:browse();break; 
case 5:add();break; 
case 6:exit(0); 
} 
} 

main() 
{ 
system("cls"); 
menu(); 
} 

#define N 100 
struct people 
{ 
char num[100]; 
char name[15]; 
char sex[20]; 
char age[20]; 
char xueli[20]; 
char gongzhi[20]; 
char address[20]; 
char telephone[20]; 
}people[N]; 


# include <stdio.h> 


enter() 
{ 
int i,n; 
printf("How many people(0-%d)?:",N-1); 
scanf("%d",&n); 
printf("\n Enter data now\n\n"); 
for(i=0;i<n;i++) 
{ 
printf("\n Input %dth people record.\n",i+1); 
input(i); 
} 
if(i!=0)save(n); 
printf_back(); 
} 


browse() 
{ 
int i,j,n; 
n=load(); 
printf_face(); 
for(i=0;i<n;i++) 
{ 
if((i!=0)&&(i%10==0)) 
{ 
printf("\n\nPass any key to continue ...."); 
getch(); 
puts("\n\n"); 
} 
printf_one(i) ; 
} 
printf("\tThere are %d record.\n",n); 
printf("\nPass any key to back ..."); 
getch(); 
menu(); 
} 


add() 
{ 
int i,n,m,k; 
FILE*fp; 
n=load(); 
printf("How many people are you want to add(0-%d)?:",N-1-n); 
scanf("%d",&m); 
k=m+n; 
for(i=n;i<k;i++) 
{ 
printf("\nInput %dth people record.\n",i-n+1 ); 
input(i); 
} 
if((fp=fopen("Pro.txt","ab"))==NULL) 
{ 
printf("cannot open file\n"); 
} 
for(i=n;i<k;i++) 
if(fwrite(&people[i],sizeof(struct people),1,fp)!=1) 
printf("file write error\n"); 
fclose(fp); 
printf_back(); 
} 


search() 
{ 
int i,n,k,w1=1,w2,w3,w4,m,a; 
struct people p; 
n=load(); 
do 
{ 
printf("\n\nWhich way do you want to choose? \n\t1).By xueli 2).By num [ ]\b\b"); 
scanf("%d",&m); 
switch(m) 
{ 
case 1: 
do 
{ k=-1; 
printf("\n\nEnter xeuli that you want to search! xueli."); 
scanf("%s",p.xueli); 
printf_face(); 
for(i=0;i<n;i++) 
if(strcmp(p.xueli,people[i].xueli)==0) 
{ k=i; 
printf_one(k);break; 
} 
if(k==-1) 
{ printf("\n\nNO exist!please"); 
printf("\n\nAre you again?\n\t1).again 2).NO and back [ ]\b\b"); 
scanf("%d",&w1); 
if(w1==2) 
printf_back(); 
} 
} 
while(k==-1&&w1==1);break; 
case 2: 
do 
{k=-1; 
printf("\n\nEnter num that you want to search! num."); 
scanf("%s",p.num); 
printf_face(); 
for(i=0;i<n;i++) 
if(strcmp(p.num,people[i].num)==0) 
{k=i; 
printf_one(k);break; 
} 
if(k==-1) 
{printf("\n\nNO exist!please"); 
printf("\n\nAre you again?\n\t1).again 2).NO and back [ ]\b\b"); 
scanf("%d",&w1); 
if(w1==2) 
printf_back(); 
} 
} 
while(k==-1&&w1==1);break; 
} 
w4=0;w3=0; 
if(k!=-1) 
{printf("\n\nWhat do you want to do?\n\t 1).Search 2).Modify 3).Delete 4).Back menu [ ]\b\b"); 
scanf("%d",&w2); 
switch(w2) 
{case 2:w3=modify_data(k,n);break; 
case 3:{printf("\nAre you sure?\n\t 1).Sure 2).No and back [ ]\b\b"); 
scanf("%d",&w4); 
if(w4==1) 
for(a=k;a<n;a++) 
{strcpy(people[a].num,people[a+1].num); 
strcpy(people[a].name,people[a+1].name); 
strcpy(people[a].sex,people[a+1].sex); 
strcpy(people[a].age,people[a+1].age); 
strcpy(people[a].xueli,people[a+1].xueli); 
strcpy(people[a].gongzhi,people[a+1].gongzhi); 
strcpy(people[a].address,people[a+1].address); 
strcpy(people[a].telephone,people[a+1].telephone); 

} 

break; 
} 
} 
if(w3==1||w4==1) 
{save(n); 
printf("\n\nSuccessful.^_^."); 
printf("\n\nWhant do you want to do? \n\t 1).Search another 2).Back [ ]\b\b" ); 
scanf("%d",&w2); 
} 
} 
} 
while(w2==1); 
menu(); 
} 


modify() 
{struct people p; 
FILE *fp; 
int i,n,k,w0=1,w1,w2=0; 
n=load(); 
do 
{ 
k=-1; 
printf_face(); 
for(i=0;i<n;i++) 
{if((i!=0)&&(i%10==0)) 
{printf("\n\nRemember NO.which needed modify.pass any key to contiune ..."); 
getch(); 
puts("\n\n"); 
} 
printf_one(i); 
} 
do 
{printf("\n\nEnter NO.that you want to modify! NO.:"); 
scanf("%s",p.num); 
for(i=0;i<n;i++) 
if(strcmp(p.num,people[i].num)==0) 
{k=i; 
p=people[i]; 
} 
if(k==-1)printf("\n\nNO exist!please again"); 
}while(k==-1); 
printf_face(); 
printf_one(k); 
w1=modify_data(k,n); 
if(w1==1) 
{printf("\nSuccessful ^_^.\n\nAre you modify another ?\n\n\t 1).Yes 2).Back with save\t[ ]\b\b"); 
scanf("%d",&w0); 
w2=1; 
} 
else 
{w0=0; 
if(w2==1) 
people[k]=p; 
} 
if(w0!=1&&w2==1) 
save(n); 
}while(w0==1); 
menu(); 
} 


save(int n) 
{FILE *fp; 
int i; 
if((fp=fopen("Pro.txt","wb"))==NULL) 
{printf("\nCannot open file\n"); 
return NULL; 
} 
for(i=0;i<n;i++) 
if(people[i].num!=0) 
if(fwrite(&people[i],sizeof(struct people),1,fp)!=1) 
printf("file write error\n"); 
fclose(fp); 
} 



load() 
{FILE *fp; 
int i; 
if((fp=fopen("Pro.txt","rb"))==NULL) 
{printf("\nCannot open file\n"); 
return NULL; 
} 
for(i=0;!feof(fp);i++) 
fread(&people[i],sizeof(struct people),1,fp); 
fclose(fp); 
return(i-1); 
} 


input(int i) 
{ 
no_input(i,i); 
printf("num:"); 
scanf("%s",people[i].num); 
printf("name:"); 
scanf("%s", people[i].name) ; 
printf("sex:"); 
scanf("%s",people[i].sex); 
printf("age:"); 
scanf("%s",people[i].age); 
printf("xueli:"); 
scanf("%s",people[i].xueli); 
printf("gongzhi:"); 
scanf("%s",people[i].gongzhi); 
printf("address:"); 
scanf("%s",people[i].address); 
printf("telephone:"); 
scanf("%s",people[i].telephone); 
} 


modify_data(int i) 
{int c,w1; 
do 
{puts("\nmodify by=>\n\n 1).num 2).name 3).sex 4).ages 5).xueli 6)gongzhi 7)address 8)telephone "); 
printf("Which you needed?:[ ]\b\b"); 
scanf("%d",&c); 
if(c>8||c<1) 
{puts("\nChoice error!Please again!"); 
getchar(); 
} 
}while(c>8||c<1); 
do 
{switch(c) 
{ 
case 1:printf("num:");scanf("%s",people[i].num);break; 
case 2:printf("name:");scanf("%s",people[i].name);break; 
case 3:printf("sex:");scanf("%s",people[i].sex);break; 
case 4:printf("age:");scanf("%s",people[i].age);break; 
case 5:printf("xueli:");scanf("%s",people[i].xueli);break; 
case 6:printf("gongzhi:");scanf("%s",people[i].gongzhi);break; 
case 7:printf("address:");scanf("%s",people[i].address);break; 
case 8:printf("telephone:");scanf("%s",people[i].telephone);break; 
} 
puts("\nNow:\n"); 
printf_face(); 
printf_one(i); 
printf("\nAre you sure?\n\n\t 1).Sure 2).No and remodify 3).Back without save in this time [ ]\b\b"); 
scanf("%d",&w1); 
} 
while(w1==2); 
return(w1); 
} 


no_input(int i,int n) 
{int j,k,w1; 
do 
{w1=0; 

for(j=0;people[i].num[j]!='\0';j++) 
if(people[i].num[j]>'9') 
{puts("Input error!Only be made up of(0-9).Please reinput!\n"); 
w1=1;break; 
} 
if(w1!=1) 
for(k=0;k<n;k++) 
if(k!=i&&strcmp(people[k].num,people[i].num)==0) 
{puts("This record is exist.please reinput!\n"); 
} 
} 
while(w1==1); 
} 


printf_face() 
{ 
printf("\nnum name sex ages xueli gongzhi address telephone \n"); 
} 


printf_one(int i) 
{ 
int j; 
printf("%7s%7s%7s%7s%7s%7s%10s%12s\n",people[i].num,people[i].name,people[i].sex,people[i].age,people 
[i].xueli,people[i].gongzhi,people[i].address,people[i].telephone); 
} 

printf_back() 
{ 
int j,w; 
printf("\n\n\tSuccessful.^_^\n\n"); 
printf("What do you want you to do?\n\n\t1).Browse all now\t2).Back: [ ]\b\b"); 
scanf("%d",&w); 
if(w==1) 
browse(); 
else menu(); 
} 
