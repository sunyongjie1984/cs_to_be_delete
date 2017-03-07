/* c1.h (程序名) */
 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> /* malloc()等 */
 #include<limits.h> /* INT_MAX等 */
 #include<stdio.h> /* EOF(=^Z或F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 /* 函数结果状态代码 */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 /* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
 typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
 typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
 
/* algo2-1.c 实现算法2.1的程序 */
 #include"c1.h"
 typedef int ElemType;


#include"c2-1.h"
/* c2-1.h 线性表的动态分配顺序存储结构 */
 #define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
 #define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
 typedef struct
 {
   ElemType *elem; /* 存储空间基址 */
   int length; /* 当前长度 */
   int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
 }SqList;

#include"bo2-1.c"
/* bo2-1.c 顺序表示的线性表(存储结构由c2-1.h定义)的基本操作(12个) */
 Status InitList(SqList *L) /* 算法2.3 */
 { /* 操作结果：构造一个空的顺序线性表 */
   (*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
   if(!(*L).elem)
     exit(OVERFLOW); /* 存储分配失败 */
   (*L).length=0; /* 空表长度为0 */
   (*L).listsize=LIST_INIT_SIZE; /* 初始存储容量 */
   return OK;
 }

 Status DestroyList(SqList *L)
 { /* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
   free((*L).elem);
   (*L).elem=NULL;
   (*L).length=0;
   (*L).listsize=0;
   return OK;
 }

 Status ClearList(SqList *L)
 { /* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
   (*L).length=0;
   return OK;
 }

 Status ListEmpty(SqList L)
 { /* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L.length==0)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SqList L)
 { /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
   return L.length;
 }

 Status GetElem(SqList L,int i,ElemType *e)
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：用e返回L中第i个数据元素的值 */
   if(i<1||i>L.length)
     exit(ERROR);
   *e=*(L.elem+i-1);
   return OK;
 }

 int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：顺序线性表L已存在，compare()是数据元素判定函数(满足为1,否则为0) */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0。算法2.6 */
   ElemType *p;
   int i=1; /* i的初值为第1个元素的位序 */
   p=L.elem; /* p的初值为第1个元素的存储位置 */
   while(i<=L.length&&!compare(*p++,e))
     ++i;
   if(i<=L.length)
     return i;
   else
     return 0;
 }

 Status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   int i=2;
   ElemType *p=L.elem+1;
   while(i<=L.length&&*p!=cur_e)
   {
     p++;
     i++;
   }
   if(i>L.length)
     return INFEASIBLE;
   else
   {
     *pre_e=*--p;
     return OK;
   }
 }

 Status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   int i=1;
   ElemType *p=L.elem;
   while(i<L.length&&*p!=cur_e)
   {
     i++;
     p++;
   }
   if(i==L.length)
     return INFEASIBLE;
   else
   {
     *next_e=*++p;
     return OK;
   }
 }

 Status ListInsert(SqList *L,int i,ElemType e) /* 算法2.4 */
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
   /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
   ElemType *newbase,*q,*p;
   if(i<1||i>(*L).length+1) /* i值不合法 */
     return ERROR;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   q=(*L).elem+i-1; /* q为插入位置 */
   for(p=(*L).elem+(*L).length-1;p>=q;--p) /* 插入位置及之后的元素右移 */
     *(p+1)=*p;
   *q=e; /* 插入e */
   ++(*L).length; /* 表长增1 */
   return OK;
 }

 Status ListDelete(SqList *L,int i,ElemType *e) /* 算法2.5 */
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
   ElemType *p,*q;
   if(i<1||i>(*L).length) /* i值不合法 */
     return ERROR;
   p=(*L).elem+i-1; /* p为被删除元素的位置 */
   *e=*p; /* 被删除元素的值赋给e */
   q=(*L).elem+(*L).length-1; /* 表尾元素的位置 */
   for(++p;p<=q;++p) /* 被删除元素之后的元素左移 */
     *(p-1)=*p;
   (*L).length--; /* 表长减1 */
   return OK;
 }

 Status ListTraverse(SqList L,void(*vi)(ElemType*))
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
   /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
   ElemType *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     vi(p++);
   printf("\n");
   return OK;
 }

 Status equal(ElemType c1,ElemType c2)
 { /* 判断是否相等的函数，Union()用到 */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void Union(SqList *La,SqList Lb) /* 算法2.1 */
 { /* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
   ElemType e;
   int La_len,Lb_len;
   int i;
   La_len=ListLength(*La); /* 求线性表的长度 */
   Lb_len=ListLength(Lb);
   for(i=1;i<=Lb_len;i++)
   {
     GetElem(Lb,i,&e); /* 取Lb中第i个数据元素赋给e */
     if(!LocateElem(*La,e,equal)) /* La中不存在和e相同的元素,则插入之 */
       ListInsert(La,++La_len,e);
   }
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb;
   Status i;
   int j;
   i=InitList(&La);
   if(i==1) /* 创建空表La成功 */
     for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
       i=ListInsert(&La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 也可不判断是否创建成功 */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     i=ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   Union(&La,Lb);
   printf("new La= "); /* 输出新表La的内容 */
   ListTraverse(La,print);}
 
/* algo2-2.c 实现算法2.2的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 void MergeList(SqList La,SqList Lb,SqList *Lc) /* 算法2.2 */
 { /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
   /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
   int i=1,j=1,k=0;
   int La_len,Lb_len;
   ElemType ai,bj;
   InitList(Lc); /* 创建空表Lc */
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   while(i<=La_len&&j<=Lb_len) /* 表La和表Lb均非空 */
   {
     GetElem(La,i,&ai);
     GetElem(Lb,j,&bj);
     if(ai<=bj)
     {
       ListInsert(Lc,++k,ai);
       ++i;
     }
     else
     {
       ListInsert(Lc,++k,bj);
       ++j;
     }
   }
   while(i<=La_len) /* 表La非空且表Lb空 */
   {
     GetElem(La,i++,&ai);
     ListInsert(Lc,++k,ai);
   }
   while(j<=Lb_len) /* 表Lb非空且表La空 */
   {
     GetElem(Lb,j++,&bj);
     ListInsert(Lc,++k,bj);
   }
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20};
   InitList(&La); /* 创建空表La */
   for(j=1;j<=4;j++) /* 在表La中插入4个元素 */
     ListInsert(&La,j,a[j-1]);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=7;j++) /* 在表Lb中插入7个元素 */
     ListInsert(&Lb,j,b[j-1]);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }



/* algo2-3.c 实现算法2.7的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 void MergeList(SqList La,SqList Lb,SqList *Lc) /* 算法2.7 */
 { /* 已知顺序线性表La和Lb的元素按值非递减排列。 */
   /* 归并La和Lb得到新的顺序线性表Lc,Lc的元素也按值非递减排列 */
   ElemType *pa,*pa_last,*pb,*pb_last,*pc;
   pa=La.elem;
   pb=Lb.elem;
   (*Lc).listsize=(*Lc).length=La.length+Lb.length;/*不用InitList()创建空表Lc */
   pc=(*Lc).elem=(ElemType *)malloc((*Lc).listsize*sizeof(ElemType));
   if(!(*Lc).elem) /* 存储分配失败 */
     exit(OVERFLOW);
   pa_last=La.elem+La.length-1;
   pb_last=Lb.elem+Lb.length-1;
   while(pa<=pa_last&&pb<=pb_last) /* 表La和表Lb均非空 */
   { /* 归并 */
     if(*pa<=*pb)
       *pc++=*pa++;
     else
       *pc++=*pb++;
   }
   while(pa<=pa_last) /* 表La非空且表Lb空 */
     *pc++=*pa++; /* 插入La的剩余元素 */
   while(pb<=pb_last) /* 表Lb非空且表La空 */
     *pc++=*pb++; /* 插入Lb的剩余元素 */
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j;
   InitList(&La); /* 创建空表La */
   for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
     ListInsert(&La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }


/* algo2-4.c 修改算法2.7的第一个循环语句中的条件语句为开关语句，且当 */
 /* *pa=*pb时，只将两者中之一插入Lc。此操作的结果和算法2.1相同 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 int comp(ElemType c1,ElemType c2)
 {
   int i;
   if(c1<c2)
     i=1;
   else if(c1==c2)
     i=0;
   else
     i=-1;
   return i;
 }

 void MergeList(SqList La,SqList Lb,SqList *Lc)
 { /* 另一种合并线性表的方法（根据算法2.7下的要求修改算法2.7） */
   ElemType  *pa,*pa_last,*pb,*pb_last,*pc;
   pa=La.elem;
   pb=Lb.elem;
   (*Lc).listsize=La.length+Lb.length; /* 此句与算法2.7不同 */
   pc=(*Lc).elem=(ElemType *)malloc((*Lc).listsize*sizeof(ElemType));
   if(!(*Lc).elem)
     exit(OVERFLOW);
   pa_last=La.elem+La.length-1;
   pb_last=Lb.elem+Lb.length-1;
   while(pa<=pa_last&&pb<=pb_last) /* 表La和表Lb均非空 */
     switch(comp(*pa,*pb)) /* 此句与算法2.7不同 */
     {
       case  0: pb++;
       case  1: *pc++=*pa++;
                break;
       case -1: *pc++=*pb++;
     }
   while(pa<=pa_last) /* 表La非空且表Lb空 */
     *pc++=*pa++;
   while(pb<=pb_last) /* 表Lb非空且表La空 */
     *pc++=*pb++;
   (*Lc).length=pc-(*Lc).elem; /* 加此句 */
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j;
   InitList(&La); /* 创建空表La */
   for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
     ListInsert(&La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }


 
/* algo2-5.c 实现算法2.11、2.12的程序 */
 #include"c1.h"
 typedef int ElemType;

 #include"c2-2.h"
/* c2-2.h 线性表的单链表存储结构 */
 struct LNode
 {
   ElemType data;
   struct LNode *next;
 };
 typedef struct LNode *LinkList; /* 另一种定义LinkList的方法 */

 #include"bo2-2.c"
/* bo2-2.c 单链表线性表(存储结构由c2-2.h定义)的基本操作(12个) */
 Status InitList(LinkList *L)
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=NULL; /* 指针域为空 */
   return OK;
 }

 Status DestroyList(LinkList *L)
 { /* 初始条件：线性表L已存在。操作结果：销毁线性表L */
   LinkList q;
   while(*L)
   {
     q=(*L)->next;
     free(*L);
     *L=q;
   }
   return OK;
 }

 Status ClearList(LinkList L) /* 不改变L */
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   LinkList p,q;
   p=L->next; /* p指向第一个结点 */
   while(p) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   L->next=NULL; /* 头结点指针域为空 */
   return OK;
 }

 Status ListEmpty(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next) /* 非空 */
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   LinkList p=L->next; /* p指向第一个结点 */
   while(p) /* 没到表尾 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType *e) /* 算法2.8 */
 { /* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* j为计数器 */
   LinkList p=L->next; /* p指向第一个结点 */
   while(p&&j<i) /* 顺指针向后查找,直到p指向第i个元素或p为空 */
   {
     p=p->next;
     j++;
   }
   if(!p||j>i) /* 第i个元素不存在 */
     return ERROR;
   *e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件: 线性表L已存在,compare()是数据元素判定函数(满足为1,否则为0) */
   /* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在,则返回值为0 */
   int i=0;
   LinkList p=L->next;
   while(p)
   {
     i++;
     if(compare(p->data,e)) /* 找到这样的数据元素 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件: 线性表L已存在 */
   /* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
   /*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE */
   LinkList q,p=L->next; /* p指向第一个结点 */
   while(p->next) /* p所指结点有后继 */
   {
     q=p->next; /* q为p的后继 */
     if(q->data==cur_e)
     {
       *pre_e=p->data;
       return OK;
     }
     p=q; /* p向后移 */
   }
   return INFEASIBLE;
 }

 Status NextElem(LinkList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE */
   LinkList p=L->next; /* p指向第一个结点 */
   while(p->next) /* p所指结点有后继 */
   {
     if(p->data==cur_e)
     {
       *next_e=p->next->data;
       return OK;
     }
     p=p->next;
   }
   return INFEASIBLE;
 }

 Status ListInsert(LinkList L,int i,ElemType e) /* 算法2.9。不改变L */
 { /* 在带头结点的单链线性表L中第i个位置之前插入元素e */
   int j=0;
   LinkList p=L,s;
   while(p&&j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   if(!p||j>i-1) /* i小于1或者大于表长 */
     return ERROR;
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 插入L中 */
   s->next=p->next;
   p->next=s;
   return OK;
 }

 Status ListDelete(LinkList L,int i,ElemType *e) /* 算法2.10。不改变L */
 { /* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
   int j=0;
   LinkList p=L,q;
   while(p->next&&j<i-1) /* 寻找第i个结点,并令p指向其前趋 */
   {
     p=p->next;
     j++;
   }
   if(!p->next||j>i-1) /* 删除位置不合理 */
     return ERROR;
   q=p->next; /* 删除并释放结点 */
   p->next=q->next;
   *e=q->data;
   free(q);
   return OK;
 }

 Status ListTraverse(LinkList L,void(*vi)(ElemType))
 /* vi的形参类型为ElemType，与bo2-1.c中相应函数的形参类型ElemType&不同 */
 { /* 初始条件：线性表L已存在 */
   /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 void CreateList(LinkList *L,int n) /* 算法2.11 */
 { /* 逆位序(插在表头)输入n个元素的值，建立带表头结构的单链线性表L */
   int i;
   LinkList p;
   *L=(LinkList)malloc(sizeof(struct LNode));
   (*L)->next=NULL; /* 先建立一个带头结点的单链表 */
   printf("请输入%d个数据\n",n);
   for(i=n;i>0;--i)
   {
     p=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
     scanf("%d",&p->data); /* 输入元素值 */
     p->next=(*L)->next; /* 插入到表头 */
     (*L)->next=p;
   }
 }

 void CreateList2(LinkList *L,int n)
 { /* 正位序(插在表尾)输入n个元素的值，建立带表头结构的单链线性表 */
   int i;
   LinkList p,q;
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 生成头结点 */
   (*L)->next=NULL;
   q=*L;
   printf("请输入%d个数据\n",n);
   for(i=1;i<=n;i++)
   {
     p=(LinkList)malloc(sizeof(struct LNode));
     scanf("%d",&p->data);
     q->next=p;
     q=q->next;
   }
   p->next=NULL;
 }

 void MergeList(LinkList La,LinkList *Lb,LinkList *Lc)/* 算法2.12 */
 { /* 已知单链线性表La和Lb的元素按值非递减排列。 */
   /* 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列 */
   LinkList pa=La->next,pb=(*Lb)->next,pc;
   *Lc=pc=La; /* 用La的头结点作为Lc的头结点 */
   while(pa&&pb)
     if(pa->data<=pb->data)
     {
       pc->next=pa;
       pc=pa;
       pa=pa->next;
     }
     else
     {
       pc->next=pb;
       pc=pb;
       pb=pb->next;
     }
   pc->next=pa?pa:pb; /* 插入剩余段 */
   free(*Lb); /* 释放Lb的头结点 */
   Lb=NULL;
 }

 void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5;
   LinkList La,Lb,Lc;
   printf("按非递减顺序, ");
   CreateList2(&La,n); /* 正位序输入n个元素的值 */
   printf("La="); /* 输出链表La的内容 */
   ListTraverse(La,visit);
   printf("按非递增顺序, ");
   CreateList(&Lb,n); /* 逆位序输入n个元素的值 */
   printf("Lb="); /* 输出链表Lb的内容 */
   ListTraverse(Lb,visit);
   MergeList(La,&Lb,&Lc); /* 按非递减顺序归并La和Lb,得到新表Lc */
   printf("Lc="); /* 输出链表Lc的内容 */
   ListTraverse(Lc,visit);
 }


/* algo2-6.c 利用单链表结构处理教科书图2.1(学生健康登记表) */
 #include"c1.h"
 #define NAMELEN 8 /* 姓名最大长度 */
 #define CLASSLEN 4 /* 班级名最大长度 */
 struct stud /* 记录的结构 */
 {
   char name[NAMELEN+1];
   long num;
   char sex;
   int age;
   char Class[CLASSLEN+1];
   int health;
 };
 typedef struct stud ElemType; /* 链表结点元素类型为结构体 */
 #include"c2-2.h"
 char sta[3][9]={"健康  ","一般  ","神经衰弱"}; /* 健康状况(3类) */
 FILE *fp;

 Status InitList(LinkList *L) /* 拷自bo2-2.c */
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=NULL; /* 指针域为空 */
   return OK;
 }

 Status ListTraverse(LinkList L,void(*vi)(ElemType)) /* 拷自bo2-2.c */
 { /* 初始条件：线性表L已存在 */
   /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 void InsertAscend(LinkList L,ElemType e) /* 此函数是由bo2-9.c中的同名函数改写 */
 { /* 按学号非降序插入 */
   LinkList q=L,p=L->next;
   while(p&&e.num>p->data.num)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 void Print(struct stud e)
 { /* 显示记录e的内容 */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" 男");
   else
     printf(" 女");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

 void ReadIn(struct stud *e)
 { /* 由键盘输入结点信息 */
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   scanf("%s",e->name);
   printf("请输入学号: ");
   scanf("%ld",&e->num);
   printf("请输入性别(m:男 f:女): ");
   scanf("%*c%c",&e->sex);
   printf("请输入年龄: ");
   scanf("%d",&e->age);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   scanf("%s",e->Class);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   scanf("%d",&e->health);
 }

 void WriteToFile(struct stud e)
 { /* 将结点信息写入fp指定的文件 */
   fwrite(&e,sizeof(struct stud),1,fp);
 }

 Status ReadFromFile(struct stud *e)
 { /* 由fp指定的文件读取结点信息到e */
   int i;
   i=fread(e,sizeof(struct stud),1,fp);
   if(i==1) /* 读取文件成功 */
     return OK;
   else
     return ERROR;
 }

 Status FindFromNum(LinkList L,long num,LinkList *p,LinkList *q)
 { /* 查找表中学号为num的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&(*q)->data.num>num) /* 因为是按学号非降序排列 */
       break;
     if(*q&&(*q)->data.num==num) /* 找到该学号 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }

 Status FindFromName(LinkList L,char name[],LinkList *p,LinkList *q)
 { /* 查找表中姓名为name的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&!strcmp((*q)->data.name,name)) /* 找到该姓名 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }

 Status DeleteElemNum(LinkList L,long num)
 { /* 删除表中学号为num的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromNum(L,num,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

 Status DeleteElemName(LinkList L,char name[])
 { /* 删除表中姓名为name的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

 void Modify(ElemType *e)
 { /* 修改结点内容 */
   char s[80];
   Print(*e); /* 显示原内容 */
   printf("请输入待修改项的内容，不修改的项按回车键保持原值:\n");
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("请输入学号: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("请输入性别(m:男 f:女): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("请输入年龄: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* 修改完毕 */
 }

 #define N 4 /* student记录的个数 */
 void main()
 {
   struct stud student[N]={{"王小林",790631,'m',18,"计91",0},
                           {"陈红",790632,'f',20,"计91",1},
                           {"刘建平",790633,'m',21,"计91",0},
                           {"张立立",790634,'m',17,"计91",2}}; /* 表的初始记录 */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* 初始化链表 */
   while(flag)
   {
     printf("1:将结构体数组student中的记录按学号非降序插入链表\n");
     printf("2:将文件中的记录按学号非降序插入链表\n");
     printf("3:键盘输入新记录，并将其按学号非降序插入链表\n");
     printf("4:删除链表中第一个有给定学号的记录\n");
     printf("5:删除链表中第一个有给定姓名的记录\n");
     printf("6:修改链表中第一个有给定学号的记录\n");
     printf("7:修改链表中第一个有给定姓名的记录\n");
     printf("8:查找链表中第一个有给定学号的记录\n");
     printf("9:查找链表中第一个有给定姓名的记录\n");
     printf("10:显示所有记录 11:将链表中的所有记录存入文件 12:结束\n");
     printf("请选择操作命令: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,student[j]);
               break;
       case 2: printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("打开文件失败!\n");
               else
               {
                 while(ReadFromFile(&e))
                   InsertAscend(T,e);
                 fclose(fp);
               }
               break;
       case 3: ReadIn(&e);
               InsertAscend(T,e);
               break;
       case 4: printf("请输入待删除记录的学号: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("没有学号为%ld的记录\n",num);
               break;
       case 5: printf("请输入待删除记录的姓名: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("没有姓名为%s的记录\n",name);
               break;
       case 6: printf("请输入待修改记录的学号: ");
               scanf("%ld%*c",&num); /* %*c吃掉回车符 */
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 7: printf("请输入待修改记录的姓名: ");
               scanf("%s%*c",name); /* %*c吃掉回车符 */
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               {
                 num=q->data.num; /* 学号存入num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 8: printf("请输入待查找记录的学号: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("请输入待查找记录的姓名: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  姓名    学号 性别 年龄 班级 健康状况\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("打开文件失败!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }



/* algo2-7.c 教科书中图2.10 静态链表示例 */
 /* 第一个结点的位置在[0].cur中，成员cur的值为0，则到链表尾 */
 #include"c1.h"
 #define N 6 /* 字符串长度 */
 typedef char ElemType[N];

 #include"c2-3.h"
/* c2-3.h 线性表的静态单链表存储结构 */
 #define MAXSIZE 100 /* 链表的最大长度 */
 typedef struct
 {
   ElemType data;
   int cur;
 }component,SLinkList[MAXSIZE];

 void main()
 {
   SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}};
   int i;
   i=s[0].cur;
   while(i) /* 输出教科书中图2.10(a)的状态 */
   {
     printf("%s ",s[i].data); /* 输出链表的当前值 */
     i=s[i].cur; /* 找到下一个 */
   }
   printf("\n");
   s[4].cur=9; /* 按教科书中图2.10(b)修改 */
   s[6].cur=8;
   s[9].cur=5;
   strcpy(s[9].data,"SHI");
   i=s[0].cur;
   while(i) /* 输出教科书中图2.10(b)的状态 */
   {
     printf("%s ",s[i].data); /* 输出链表的当前值 */
     i=s[i].cur; /* 找到下一个 */
   }
   printf("\n");
 }


/* algo2-8.c 实现算法2.17的程序 */
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.c"
/* bo2-3.c 实现算法2.15、2.16的程序 (数据结构由c2-3.h定义) (3个) */
 int Malloc(SLinkList space) /* 算法2.15 */
 { /* 若备用链表非空,则返回分配的结点下标(备用链表的第一个结点),否则返回0 */
   int i=space[0].cur;
   if(i) /* 备用链表非空 */
     space[0].cur=space[i].cur; /* 备用链表的头结点指向原备用链表的第二个结点 */
   return i; /* 返回新开辟结点的坐标 */
 }

 void Free(SLinkList space,int k) /* 算法2.16 */
 { /* 将下标为k的空闲结点回收到备用链表(成为备用链表的第一个结点) */
   space[k].cur=space[0].cur; /* 回收结点的＂游标＂指向备用链表的第一个结点 */
   space[0].cur=k; /* 备用链表的头结点指向新回收的结点 */
 }

 void DestroyList()
 { /* 静态数组不能被销毁 */
 }
 #include"bo2-32.c"
/* bo2-32.c 一个数组可生成若干静态链表(数据结构由c2-3.h定义)的基本操作(12个) */
 void InitSpace(SLinkList L) /* 算法2.14。另加 */
 { /* 将一维数组L中各分量链成一个备用链表，L[0].cur为头指针。“0”表示空指针 */
   int i;
   for(i=0;i<MAXSIZE-1;i++)
     L[i].cur=i+1;
   L[MAXSIZE-1].cur=0;
 }

 int InitList(SLinkList L)
 { /* 构造一个空链表，返回值为空表在数组中的位序 */
   int i;
   i=Malloc(L); /* 调用Malloc()，简化程序 */
   L[i].cur=0; /* 空链表的表头指针为空(0) */
   return i;
 }

 Status ClearList(SLinkList L,int n)
 { /* 初始条件：L中表头位序为n的静态链表已存在。操作结果：将此表重置为空表 */
   int j,k,i=L[n].cur; /* 链表第一个结点的位置 */
   L[n].cur=0; /* 链表空 */
   k=L[0].cur; /* 备用链表第一个结点的位置 */
   L[0].cur=i; /* 把链表的结点连到备用链表的表头 */
   while(i) /* 没到链表尾 */
   {
     j=i;
     i=L[i].cur; /* 指向下一个元素 */
   }
   L[j].cur=k; /* 备用链表的第一个结点接到链表的尾部 */
   return OK;
 }

 Status ListEmpty(SLinkList L,int n)
 { /* 判断L中表头位序为n的链表是否空,若是空表返回TRUE;否则返回FALSE */
   if(L[n].cur==0) /* 空表 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SLinkList L,int n)
 { /* 返回L中表头位序为n的链表的数据元素个数 */
   int j=0,i=L[n].cur; /* i指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     i=L[i].cur; /* 指向下一个元素 */
     j++;
   }
   return j;
 }

 Status GetElem(SLinkList L,int n, int i,ElemType *e)
 { /* 用e返回L中表头位序为n的链表的第i个元素的值 */
   int l,k=n; /* k指向表头序号 */
   if(i<1||i>ListLength(L,n)) /* i值不合理 */
     return ERROR;
   for(l=1;l<=i;l++) /* 移动i-1个元素 */
     k=L[k].cur;
   *e=L[k].data;
   return OK;
 }

 int LocateElem(SLinkList L,int n,ElemType e)
 { /* 在L中表头位序为n的静态单链表中查找第1个值为e的元素。 */
   /* 若找到，则返回它在L中的位序，否则返回0 */
   int i=L[n].cur; /* i指示表中第一个结点 */
   while(i&&L[i].data!=e) /* 在表中顺链查找(e不能是字符串) */
     i=L[i].cur;
   return i;
 }

 Status PriorElem(SLinkList L,int n,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：在L中表头位序为n的静态单链表已存在 */
   /* 操作结果：若cur_e是此单链表的数据元素，且不是第一个， */
   /*           则用pre_e返回它的前驱，否则操作失败，pre_e无定义 */
   int j,i=L[n].cur; /* i为链表第一个结点的位置 */
   do
   { /* 向后移动结点 */
     j=i;
     i=L[i].cur;
   }while(i&&cur_e!=L[i].data);
   if(i) /* 找到该元素 */
   {
     *pre_e=L[j].data;
     return OK;
   }
   return ERROR;
 }

 Status NextElem(SLinkList L,int n,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：在L中表头位序为n的静态单链表已存在 */
   /* 操作结果：若cur_e是此单链表的数据元素，且不是最后一个， */
   /* 则用next_e返回它的后继，否则操作失败，next_e无定义 */
   int i;
   i=LocateElem(L,n,cur_e); /* 在链表中查找第一个值为cur_e的元素的位置 */
   if(i) /* 在静态单链表中存在元素cur_e */
   {
     i=L[i].cur; /* cur_e的后继的位置 */
     if(i) /* cur_e有后继 */
     {
       *next_e=L[i].data;
       return OK; /* cur_e元素有后继 */
     }
   }
   return ERROR; /* L不存在cur_e元素,cur_e元素无后继 */
 }

 Status ListInsert(SLinkList L,int n,int i,ElemType e)
 { /* 在L中表头位序为n的链表的第i个元素之前插入新的数据元素e */
   int l,j,k=n; /* k指向表头 */
   if(i<1||i>ListLength(L,n)+1)
     return ERROR;
   j=Malloc(L); /* 申请新单元 */
   if(j) /* 申请成功 */
   {
     L[j].data=e; /* 赋值给新单元 */
     for(l=1;l<i;l++) /* 移动i-1个元素 */
       k=L[k].cur;
     L[j].cur=L[k].cur;
     L[k].cur=j;
     return OK;
   }
   return ERROR;
 }

 Status ListDelete(SLinkList L,int n,int i,ElemType *e)
 { /* 删除在L中表头位序为n的链表的第i个数据元素e，并返回其值 */
   int j,k=n; /* k指向表头 */
   if(i<1||i>ListLength(L,n))
     return ERROR;
   for(j=1;j<i;j++) /* 移动i-1个元素 */
     k=L[k].cur;
   j=L[k].cur;
   L[k].cur=L[j].cur;
   *e=L[j].data;
   Free(L,j);
   return OK;
 }

 Status ListTraverse(SLinkList L,int n,void(*vi)(ElemType))
 { /* 依次对L中表头位序为n的链表的每个数据元素,调用函数vi()。一旦vi()失败,则操作失败 */
   int i=L[n].cur; /* 指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     vi(L[i].data); /* 调用vi() */
     i=L[i].cur; /* 指向下一个元素 */
   }
   printf("\n");
   return OK;
 }

 void difference(SLinkList space,int *S) /* 算法2.17 */
 { /* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，S为其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
   int r,p,m,n,i,j,k;
   ElemType b;
   InitSpace(space); /* 初始化备用空间 */
   *S=Malloc(space); /* 生成S的头结点 */
   r=*S; /* r指向S的当前最后结点 */
   printf("请输入集合A和B的元素个数m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c吃掉回车符 */
   printf("请输入集合A的元素（共%d个）:",m);
   for(j=1;j<=m;j++) /* 建立集合A的链表 */
   {
     i=Malloc(space); /* 分配结点 */
     scanf("%c",&space[i].data); /* 输入A的元素值 */
     space[r].cur=i; /* 插入到表尾 */
     r=i;
   }
   scanf("%*c"); /* %*c吃掉回车符 */
   space[r].cur=0; /* 尾结点的指针为空 */
   printf("请输入集合B的元素（共%d个）:",n);
   for(j=1;j<=n;j++)
   { /* 依次输入B的元素,若不在当前表中,则插入,否则删除 */
     scanf("%c",&b);
     p=*S;
     k=space[*S].cur; /* k指向集合A中的第一个结点 */
     while(k!=space[r].cur&&space[k].data!=b)
     { /* 在当前表中查找 */
       p=k;
       k=space[k].cur;
     }
     if(k==space[r].cur)
     { /* 当前表中不存在该元素，插入在r所指结点之后，且r的位置不变 */
       i=Malloc(space);
       space[i].data=b;
       space[i].cur=space[r].cur;
       space[r].cur=i;
     }
     else /* 该元素已在表中，删除之 */
     {
       space[p].cur=space[k].cur;
       Free(space,k);
       if(r==k)
         r=p; /* 若删除的是尾元素，则需修改尾指针 */
     }
   }
 }

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 void main()
 {
   int k;
   SLinkList s;
   difference(s,&k);
   ListTraverse(s,k,visit);
 }


/* algo2-9.c 尽量采用bo2-32.c中的基本操作实现算法2.17的功能 */
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.c"
 #include"bo2-32.c"

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 int difference(SLinkList space) /* 改进算法2.17(尽量利用基本操作实现) */
 { /* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，并返回其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
   int m,n,i,j,k,S;
   ElemType b,c;
   InitSpace(space); /* 初始化备用空间 */
   S=InitList(space); /* 生成链表S的头结点 */
   printf("请输入集合A和B的元素个数m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c吃掉回车符 */
   printf("请输入集合A的元素（共%d个）:",m);
   for(j=1;j<=m;j++) /* 建立集合A的链表 */
   {
     scanf("%c",&b); /* 输入A的元素值 */
     ListInsert(space,S,j,b); /* 插入到表尾 */
   }
   scanf("%*c"); /* 吃掉回车符 */
   printf("请输入集合B的元素（共%d个）:",n);
   for(j=1;j<=n;j++)
   { /* 依次输入B的元素,若不在当前表中,则插入,否则删除 */
     scanf("%c",&b);
     k=LocateElem(space,S,b); /* k为b的位序 */
     if(k) /* b在当前表中 */
     {
       PriorElem(space,S,b,&c); /* b的前驱为c */
       i=LocateElem(space,S,c); /* i为c的位序 */
       space[i].cur=space[k].cur; /* 将k的指针赋给i的指针 */
       Free(space,k); /* 将下标为k的空闲结点回收到备用链表 */
     }
     else
       ListInsert(space,S,ListLength(space,S)+1,b); /* 在表尾插入b */
   }
   return S;
 }

 void main()
 {
   int k;
   SLinkList s;
   k=difference(s);
   ListTraverse(s,k,visit);
 }


/* algo2-10.c 两个仅设表尾指针的循环链表的合并（教科书图2.13） */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
/* c2-4.h 线性表的双向链表存储结构 */
 typedef struct DuLNode
 {
   ElemType data;
   struct DuLNode *prior,*next;
 }DuLNode,*DuLinkList;

 #include"bo2-4.c"
/* bo2-4.c 设立尾指针的单循环链表(存储结构由c2-2.h定义)的12个基本操作 */
 Status InitList_CL(LinkList *L)
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=*L; /* 指针域指向头结点 */
   return OK;
 }

 Status DestroyList_CL(LinkList *L)
 { /* 操作结果：销毁线性表L */
   LinkList q,p=(*L)->next; /* p指向头结点 */
   while(p!=*L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   free(*L);
   *L=NULL;
   return OK;
 }

 Status ClearList_CL(LinkList *L) /* 改变L */
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   LinkList p,q;
   *L=(*L)->next; /* L指向头结点 */
   p=(*L)->next; /* p指向第一个结点 */
   while(p!=*L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   (*L)->next=*L; /* 头结点指针域指向自身 */
   return OK;
 }

 Status ListEmpty_CL(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next==L) /* 空 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength_CL(LinkList L)
 { /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   LinkList p=L->next; /* p指向头结点 */
   while(p!=L) /* 没到表尾 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem_CL(LinkList L,int i,ElemType *e)
 { /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* 初始化,j为计数器 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   if(i<=0||i>ListLength_CL(L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i)
   { /* 顺指针向后查找,直到p指向第i个元素 */
     p=p->next;
     j++;
   }
   *e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0 */
   int i=0;
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L->next)
   {
     i++;
     if(compare(p->data,e)) /* 满足关系 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   LinkList q,p=L->next->next; /* p指向第一个结点 */
   q=p->next;
   while(q!=L->next) /* p没到表尾 */
   {
     if(q->data==cur_e)
     {
       *pre_e=p->data;
       return TRUE;
     }
     p=q;
     q=q->next;
   }
   return FALSE;
 }

 Status NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L) /* p没到表尾 */
   {
     if(p->data==cur_e)
     {
       *next_e=p->next->data;
       return TRUE;
     }
     p=p->next;
   }
   return FALSE;
 }

 Status ListInsert_CL(LinkList *L,int i,ElemType e) /* 改变L */
 { /* 在L的第i个位置之前插入元素e */
   LinkList p=(*L)->next,s; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(*L)+1) /* 无法在第i个元素之前插入 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 插入L中 */
   s->next=p->next;
   p->next=s;
   if(p==*L) /* 改变尾结点 */
     *L=s;
   return OK;
 }

 Status ListDelete_CL(LinkList *L,int i,ElemType *e) /* 改变L */
 { /* 删除L的第i个元素,并由e返回其值 */
   LinkList p=(*L)->next,q; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(*L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   q=p->next; /* q指向待删除结点 */
   p->next=q->next;
   *e=q->data;
   if(*L==q) /* 删除的是表尾元素 */
     *L=p;
   free(q); /* 释放待删除结点 */
   return OK;
 }

 Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
 { /* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next->next;
   while(p!=L->next)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 void MergeList_CL(LinkList *La,LinkList Lb)
 {
   LinkList p=Lb->next;
   Lb->next=(*La)->next;
   (*La)->next=p->next;
   free(p);
   *La=Lb;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5,i;
   LinkList La,Lb;
   InitList_CL(&La);
   for(i=1;i<=n;i++)
     ListInsert_CL(&La,i,i);
   printf("La="); /* 输出链表La的内容 */
   ListTraverse_CL(La,visit);
   InitList_CL(&Lb);
   for(i=1;i<=n;i++)
     ListInsert_CL(&Lb,1,i*2);
   printf("Lb="); /* 输出链表Lb的内容 */
   ListTraverse_CL(Lb,visit);
   MergeList_CL(&La,Lb);
   printf("La+Lb="); /* 输出合并后的链表的内容 */
   ListTraverse_CL(La,visit);
 }


/* algo2-11.c 实现算法2.20、2.21的程序 */
 #include"c1.h"
 typedef int ElemType;

 #include"c2-5.h"
/* c2-5.h 带头结点的线性链表类型 */
 typedef struct LNode /* 结点类型 */
 {
   ElemType data;
   struct LNode *next;
 }LNode,*Link,*Position;

 typedef struct LinkList /* 链表类型 */
 {
   Link head,tail; /* 分别指向线性链表中的头结点和最后一个结点 */
   int len; /* 指示线性链表中数据元素的个数 */
 }LinkList;

 #include"bo2-6.c"
/* bo2-6.c 具有实用意义的线性链表(存储结构由c2-5.h定义)的24个基本操作 */
 Status MakeNode(Link *p,ElemType e)
 { /* 分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR */
   *p=(Link)malloc(sizeof(LNode));
   if(!*p)
     return ERROR;
   (*p)->data=e;
   return OK;
 }

 void FreeNode(Link *p)
 { /* 释放p所指结点 */
   free(*p);
   *p=NULL;
 }

 Status InitList(LinkList *L)
 { /* 构造一个空的线性链表 */
   Link p;
   p=(Link)malloc(sizeof(LNode)); /* 生成头结点 */
   if(p)
   {
     p->next=NULL;
     (*L).head=(*L).tail=p;
     (*L).len=0;
     return OK;
   }
   else
     return ERROR;
 }

 Status ClearList(LinkList *L)
 { /* 将线性链表L重置为空表，并释放原链表的结点空间 */
   Link p,q;
   if((*L).head!=(*L).tail)/* 不是空表 */
   {
     p=q=(*L).head->next;
     (*L).head->next=NULL;
     while(p!=(*L).tail)
     {
       p=q->next;
       free(q);
       q=p;
     }
     free(q);
     (*L).tail=(*L).head;
     (*L).len=0;
   }
   return OK;
 }

 Status DestroyList(LinkList *L)
 { /* 销毁线性链表L，L不再存在 */
   ClearList(L); /* 清空链表 */
   FreeNode(&(*L).head);
   (*L).tail=NULL;
   (*L).len=0;
   return OK;
 }

 Status InsFirst(LinkList *L,Link h,Link s) /* 形参增加L,因为需修改L */
 { /* h指向L的一个结点，把h当做头结点，将s所指结点插入在第一个结点之前 */
   s->next=h->next;
   h->next=s;
   if(h==(*L).tail) /* h指向尾结点 */
     (*L).tail=h->next; /* 修改尾指针 */
   (*L).len++;
   return OK;
 }

 Status DelFirst(LinkList *L,Link h,Link *q) /* 形参增加L,因为需修改L */
 { /* h指向L的一个结点，把h当做头结点，删除链表中的第一个结点并以q返回。 */
   /* 若链表为空(h指向尾结点)，q=NULL，返回FALSE */
   *q=h->next;
   if(*q) /* 链表非空 */
   {
     h->next=(*q)->next;
     if(!h->next) /* 删除尾结点 */
       (*L).tail=h; /* 修改尾指针 */
     (*L).len--;
     return OK;
   }
   else
     return FALSE; /* 链表空 */
 }

 Status Append(LinkList *L,Link s)
 { /* 将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的 */
   /* 一串结点链接在线性链表L的最后一个结点之后,并改变链表L的尾指针指向新 */
   /* 的尾结点 */
   int i=1;
   (*L).tail->next=s;
   while(s->next)
   {
     s=s->next;
     i++;
   }
   (*L).tail=s;
   (*L).len+=i;
   return OK;
 }

 Position PriorPos(LinkList L,Link p)
 { /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置 */
   /* 若无前驱，则返回NULL */
   Link q;
   q=L.head->next;
   if(q==p) /* 无前驱 */
     return NULL;
   else
   {
     while(q->next!=p) /* q不是p的直接前驱 */
       q=q->next;
     return q;
   }
 }

 Status Remove(LinkList *L,Link *q)
 { /* 删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点 */
   Link p=(*L).head;
   if((*L).len==0) /* 空表 */
   {
     *q=NULL;
     return FALSE;
   }
   while(p->next!=(*L).tail)
     p=p->next;
   *q=(*L).tail;
   p->next=NULL;
   (*L).tail=p;
   (*L).len--;
   return OK;
 }

 Status InsBefore(LinkList *L,Link *p,Link s)
 { /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前， */
   /* 并修改指针p指向新插入的结点 */
   Link q;
   q=PriorPos(*L,*p); /* q是p的前驱 */
   if(!q) /* p无前驱 */
     q=(*L).head;
   s->next=*p;
   q->next=s;
   *p=s;
   (*L).len++;
   return OK;
 }

 Status InsAfter(LinkList *L,Link *p,Link s)
 { /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后， */
   /* 并修改指针p指向新插入的结点 */
   if(*p==(*L).tail) /* 修改尾指针 */
     (*L).tail=s;
   s->next=(*p)->next;
   (*p)->next=s;
   *p=s;
   (*L).len++;
   return OK;
 }

 Status SetCurElem(Link p,ElemType e)
 { /* 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值 */
   p->data=e;
   return OK;
 }

 ElemType GetCurElem(Link p)
 { /* 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值 */
   return p->data;
 }

 Status ListEmpty(LinkList L)
 { /* 若线性链表L为空表，则返回TRUE，否则返回FALSE */
   if(L.len)
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* 返回线性链表L中元素个数 */
   return L.len;
 }

 Position GetHead(LinkList L)
 { /* 返回线性链表L中头结点的位置 */
   return L.head;
 }

 Position GetLast(LinkList L)
 { /* 返回线性链表L中最后一个结点的位置 */
   return L.tail;
 }

 Position NextPos(Link p)
 { /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置 */
   /* 若无后继，则返回NULL */
   return p->next;
 }

 Status LocatePos(LinkList L,int i,Link *p)
 { /* 返回p指示线性链表L中第i个结点的位置，并返回OK，i值不合法时返回ERROR */
   /* i=0为头结点 */
   int j;
   if(i<0||i>L.len)
     return ERROR;
   else
   {
     *p=L.head;
     for(j=1;j<=i;j++)
       *p=(*p)->next;
     return OK;
   }
 }

 Position LocateElem(LinkList L,ElemType e,Status (*compare)(ElemType,ElemType))
 { /* 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置， */
   /* 若不存在这样的元素，则返回NULL */
   Link p=L.head;
   do
     p=p->next;
   while(p&&!(compare(p->data,e))); /* 没到表尾且没找到满足关系的元素 */
   return p;
 }

 Status ListTraverse(LinkList L,void(*visit)(ElemType))
 { /* 依次对L的每个数据元素调用函数visit()。一旦visit()失败，则操作失败 */
   Link p=L.head->next;
   int j;
   for(j=1;j<=L.len;j++)
   {
     visit(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 Status OrderInsert(LinkList *L,ElemType e,int (*comp)(ElemType,ElemType))
 { /* 已知L为有序线性链表，将元素e按非降序插入在L中。（用于一元多项式） */
   Link o,p,q;
   q=(*L).head;
   p=q->next;
   while(p!=NULL&&comp(p->data,e)<0) /* p不是表尾且元素值小于e */
   {
     q=p;
     p=p->next;
   }
   o=(Link)malloc(sizeof(LNode)); /* 生成结点 */
   o->data=e; /* 赋值 */
   q->next=o; /* 插入 */
   o->next=p;
   (*L).len++; /* 表长加1 */
   if(!p) /* 插在表尾 */
     (*L).tail=o; /* 修改尾结点 */
   return OK;
 }

 Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType))
 { /* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
   /* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
   /* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
   Link p=L.head,pp;
   do
   {
     pp=p;
     p=p->next;
   }while(p&&(compare(p->data,e)<0)); /* 没到表尾且p->data.expn<e.expn */
   if(!p||compare(p->data,e)>0) /* 到表尾或compare(p->data,e)>0 */
   {
     *q=pp;
     return FALSE;
   }
   else /* 找到 */
   {
     *q=p;
     return TRUE;
   }
 }

 Status ListInsert_L(LinkList *L,int i,ElemType e) /* 算法2.20 */
 { /* 在带头结点的单链线性表L的第i个元素之前插入元素e */
   Link h,s;
   if(!LocatePos(*L,i-1,&h))
     return ERROR; /* i值不合法 */
   if(!MakeNode(&s,e))
     return ERROR; /* 结点分配失败 */
   InsFirst(L,h,s); /*对于从第i个结点开始的链表,第i-1个结点是它的头结点 */
   return OK;
 }

 Status MergeList_L(LinkList La,LinkList Lb,LinkList *Lc,int(*compare)(ElemType,ElemType))
 { /* 已知单链线性表La和Lb的元素按值非递减排列。归并La和Lb得到新的单链 */
   /* 线性表Lc，Lc的元素也按值非递减排列。（不改变La、Lb）算法2.21 */
   Link ha,hb,pa,pb,q;
   ElemType a,b;
   if(!InitList(Lc))
     return ERROR; /* 存储空间分配失败 */
   ha=GetHead(La); /* ha和hb分别指向La和Lb的头结点 */
   hb=GetHead(Lb);
   pa=NextPos(ha); /* pa和pb分别指向La和Lb的第一个结点 */
   pb=NextPos(hb);
   while(!ListEmpty(La)&&!ListEmpty(Lb)) /* La和Lb均非空 */
   {
     a=GetCurElem(pa); /* a和b为两表中当前比较元素 */
     b=GetCurElem(pb);
     if(compare(a,b)<=0)
     {
       DelFirst(&La,ha,&q);
       InsFirst(Lc,(*Lc).tail,q);
       pa=NextPos(ha);
     }
     else /* a>b */
     {
       DelFirst(&Lb,hb,&q);
       InsFirst(Lc,(*Lc).tail,q);
       pb=NextPos(hb);
     }
   }
   if(!ListEmpty(La))
     Append(Lc,pa);
   else
     Append(Lc,pb);
   FreeNode(&ha);
   FreeNode(&hb);
   return OK;
 }

 int comp(ElemType c1,ElemType c2)
 {
   return c1-c2;
 }

 void visit(ElemType c)
 {
   printf("%d ",c); /* 整型 */
 }

 void main()
 {
   LinkList La,Lb,Lc;
   int j;
   InitList(&La);
   for(j=1;j<=5;j++)
     ListInsert_L(&La,j,j); /* 顺序插入 1 2 3 4 5 */
   printf("La=");
   ListTraverse(La,visit);
   InitList(&Lb);
   for(j=1;j<=5;j++)
     ListInsert_L(&Lb,j,2*j); /* 顺序插入 2 4 6 8 10 */
   printf("Lb=");
   ListTraverse(Lb,visit);
   InitList(&Lc);
   MergeList_L(La,Lb,&Lc,comp); /* 归并La和Lb，产生Lc */
   printf("Lc=");
   ListTraverse(Lc,visit);
   DestroyList(&Lc);
 }


/* algo2-12.c 用单链表实现算法2.1,仅有4句与algo2-1.c不同 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 此句与algo2-1.c不同(因为采用不同的结构) */
 #include"bo2-2.c" /* 此句与algo2-1.c不同(因为采用不同的结构) */

 Status equal(ElemType c1,ElemType c2)
 { /* 判断是否相等的函数，Union()用到 */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void Union(LinkList La,LinkList Lb) /* 算法2.1,此句与algo2-1.c不同 */
 { /* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
   ElemType e;
   int La_len,Lb_len;
   int i;
   La_len=ListLength(La); /* 求线性表的长度 */
   Lb_len=ListLength(Lb);
   for(i=1;i<=Lb_len;i++)
   {
     GetElem(Lb,i,&e); /* 取Lb中第i个数据元素赋给e */
     if(!LocateElem(La,e,equal)) /* La中不存在和e相同的元素,则插入之 */
       ListInsert(La,++La_len,e);
   }
 }

 void print(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList La,Lb; /* 此句与algo2-1.c不同(因为采用不同的结构) */
   Status i;
   int j;
   i=InitList(&La);
   if(i==1) /* 创建空表La成功 */
     for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
       i=ListInsert(La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 也可不判断是否创建成功 */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     i=ListInsert(Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   Union(La,Lb);
   printf("new La= "); /* 输出新表La的内容 */
   ListTraverse(La,print);
 } 


/* algo2-13.c 采用链表结构实现算法2.2的程序，仅有4句与algo2-2.c不同 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 此句与algo2-2.c不同 */
 #include"bo2-2.c" /* 此句与algo2-2.c不同 */

 void MergeList(LinkList La,LinkList Lb,LinkList *Lc) /* 算法2.2,此句与algo2-2.c不同 */
 { /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
   /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
   int i=1,j=1,k=0;
   int La_len,Lb_len;
   ElemType ai,bj;
   InitList(Lc); /* 创建空表Lc */
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   while(i<=La_len&&j<=Lb_len) /* 表La和表Lb均非空 */
   {
     GetElem(La,i,&ai);
     GetElem(Lb,j,&bj);
     if(ai<=bj)
     {
       ListInsert(*Lc,++k,ai);
       ++i;
     }
     else
     {
       ListInsert(*Lc,++k,bj);
       ++j;
     }
   }
   while(i<=La_len) /* 表La非空且表Lb空 */
   {
     GetElem(La,i++,&ai);
     ListInsert(*Lc,++k,ai);
   }
   while(j<=Lb_len) /* 表Lb非空且表La空 */
   {
     GetElem(Lb,j++,&bj);
     ListInsert(*Lc,++k,bj);
   }
 }

 void print(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList La,Lb,Lc; /* 此句与algo2-2.c不同 */
   int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20};
   InitList(&La); /* 创建空表La */
   for(j=1;j<=4;j++) /* 在表La中插入4个元素 */
     ListInsert(La,j,a[j-1]);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=7;j++) /* 在表Lb中插入7个元素 */
     ListInsert(Lb,j,b[j-1]);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }
 
/* algo4-1.c 实现算法4.6、4.7的程序 */
 #include"c1.h"

 #include"c4-1.h"
/* c4-1.h 串的定长顺序存储表示 */
 #define MAXSTRLEN 40 /* 用户可在255以内定义最大串长（1个字节） */
 typedef char SString[MAXSTRLEN+1]; /* 0号单元存放串的长度 */

 #include"bo4-1.c"
/* bo4-1.c 串采用定长顺序存储结构(由c4-1.h定义)的基本操作(14个) */
 /* SString是数组，故不需引用类型。此基本操作包括算法4.2,4.3,4.5 */
 Status StrAssign(SString T,char *chars)
 { /* 生成一个其值等于chars的串T */
   int i;
   if(strlen(chars)>MAXSTRLEN)
     return ERROR;
   else
   {
     T[0]=strlen(chars);
     for(i=1;i<=T[0];i++)
       T[i]=*(chars+i-1);
     return OK;
   }
 }

 Status StrCopy(SString T,SString S)
 { /* 由串S复制得串T */
   int i;
   for(i=0;i<=S[0];i++)
     T[i]=S[i];
   return OK;
 }

 Status StrEmpty(SString S)
 { /* 若S为空串,则返回TRUE,否则返回FALSE */
   if(S[0]==0)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(SString S,SString T)
 { /* 初始条件: 串S和T存在 */
   /* 操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
   int i;
   for(i=1;i<=S[0]&&i<=T[0];++i)
     if(S[i]!=T[i])
       return S[i]-T[i];
   return S[0]-T[0];
 }

 int StrLength(SString S)
 { /* 返回串的元素个数 */
   return S[0];
 }

 Status ClearString(SString S)
 { /* 初始条件:串S存在。操作结果:将S清为空串 */
   S[0]=0;/* 令串长为零 */
   return OK;
 }

 Status Concat(SString T,SString S1,SString S2) /* 算法4.2改 */
 { /* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
   int i;
   if(S1[0]+S2[0]<=MAXSTRLEN)
   { /* 未截断 */
     for(i=1;i<=S1[0];i++)
       T[i]=S1[i];
     for(i=1;i<=S2[0];i++)
       T[S1[0]+i]=S2[i];
     T[0]=S1[0]+S2[0];
     return TRUE;
   }
   else
   { /* 截断S2 */
     for(i=1;i<=S1[0];i++)
       T[i]=S1[i];
     for(i=1;i<=MAXSTRLEN-S1[0];i++)
       T[S1[0]+i]=S2[i];
     T[0]=MAXSTRLEN;
     return FALSE;
   }
 }

 Status SubString(SString Sub,SString S,int pos,int len)
 { /* 用Sub返回串S的第pos个字符起长度为len的子串。算法4.3 */
   int i;
   if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
     return ERROR;
   for(i=1;i<=len;i++)
     Sub[i]=S[pos+i-1];
   Sub[0]=len;
   return OK;
 }

 int Index(SString S,SString T,int pos)
 { /* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数值为0。 */
   /* 其中,T非空,1≤pos≤StrLength(S)。算法4.5 */
   int i,j;
   if(1<=pos&&pos<=S[0])
   {
     i=pos;
     j=1;
     while(i<=S[0]&&j<=T[0])
       if(S[i]==T[j]) /* 继续比较后继字符 */
       {
         ++i;
         ++j;
       }
       else /* 指针后退重新开始匹配 */
       {
         i=i-j+2;
         j=1;
       }
     if(j>T[0])
       return i-T[0];
     else
       return 0;
   }
   else
     return 0;
 }

 Status StrInsert(SString S,int pos,SString T)
 { /* 初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
   /* 操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */
   int i;
   if(pos<1||pos>S[0]+1)
     return ERROR;
   if(S[0]+T[0]<=MAXSTRLEN)
   { /* 完全插入 */
     for(i=S[0];i>=pos;i--)
       S[i+T[0]]=S[i];
     for(i=pos;i<pos+T[0];i++)
       S[i]=T[i-pos+1];
     S[0]=S[0]+T[0];
     return TRUE;
   }
   else
   { /* 部分插入 */
     for(i=MAXSTRLEN;i<=pos;i--)
       S[i]=S[i-T[0]];
     for(i=pos;i<pos+T[0];i++)
       S[i]=T[i-pos+1];
     S[0]=MAXSTRLEN;
     return FALSE;
   }
 }

 Status StrDelete(SString S,int pos,int len)
 { /* 初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
   /* 操作结果: 从串S中删除第pos个字符起长度为len的子串 */
   int i;
   if(pos<1||pos>S[0]-len+1||len<0)
     return ERROR;
   for(i=pos+len;i<=S[0];i++)
     S[i-len]=S[i];
   S[0]-=len;
   return OK;
 }

 Status Replace(SString S,SString T,SString V)
 { /* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
   /* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
   int i=1; /* 从串S的第一个字符起查找串T */
   if(StrEmpty(T)) /* T是空串 */
     return ERROR;
   do
   {
     i=Index(S,T,i); /* 结果i为从上一个i之后找到的子串T的位置 */
     if(i) /* 串S中存在串T */
     {
       StrDelete(S,i,StrLength(T)); /* 删除该串T */
       StrInsert(S,i,V); /* 在原串T的位置插入串V */
       i+=StrLength(V); /* 在插入的串V后面继续查找串T */
     }
   }while(i);
   return OK;
 }

 void DestroyString()
 { /* 由于SString是定长类型,无法销毁 */
 }

 void StrPrint(SString T)
 { /* 输出字符串T。另加 */
   int i;
   for(i=1;i<=T[0];i++)
     printf("%c",T[i]);
   printf("\n");
 }

 void get_next(SString T,int next[])
 { /* 求模式串T的next函数值并存入数组next 算法 4.7 */
   int i=1,j=0;
   next[1]=0;
   while(i<T[0])
     if(j==0||T[i]==T[j])
     {
       ++i;
       ++j;
       next[i]=j;
     }
     else
       j=next[j];
 }

 int Index_KMP(SString S,SString T,int pos,int next[])
 { /* 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法。 */
   /* 其中,T非空,1≤pos≤StrLength(S)。算法 4.6 */
   int i=pos,j=1;
   while(i<=S[0]&&j<=T[0])
     if(j==0||S[i]==T[j]) /* 继续比较后继字符 */
     {
       ++i;
       ++j;
     }
     else /* 模式串向右移动 */
       j=next[j];
   if(j>T[0]) /* 匹配成功 */
     return i-T[0];
   else
     return 0;
 }

 void main()
 {
   int i,j,*p;
   SString s1,s2; /* 以教科书中图4.5为例 */
   StrAssign(s1,"acabaabaabcacaabc");
   printf("主串为: ");
   StrPrint(s1);
   StrAssign(s2,"abaabcac");
   printf("子串为: ");
   StrPrint(s2);
   i=StrLength(s2);
   p=(int*)malloc((i+1)*sizeof(int)); /* 生成s2的next数组 */
   get_next(s2,p);
   printf("子串的next函数为: ");
   for(j=1;j<=i;j++)
     printf("%d ",*(p+j));
   printf("\n");
   i=Index_KMP(s1,s2,1,p);
   if(i)
     printf("主串和子串在第%d个字符处首次匹配\n",i);
   else
     printf("主串和子串匹配不成功\n");
 }
 
/* algo5-1.c 实现算法5.2的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-2.h"
/* c5-2.h 稀疏矩阵的三元组顺序表存储表示 */
 #define MAXSIZE 100 /* 非零元个数的最大值 */
 typedef struct
 {
   int i,j; /* 行下标,列下标 */
   ElemType e; /* 非零元素值 */
 }Triple;
 typedef struct
 {
   Triple data[MAXSIZE+1]; /* 非零元三元组表,data[0]未用 */
   int mu,nu,tu; /* 矩阵的行数、列数和非零元个数 */
 }TSMatrix;

 #include"bo5-2.c"
/* bo5-2.c 三元组稀疏矩阵的基本操作,包括算法5.1(9个) */
 Status CreateSMatrix(TSMatrix *M)
 { /* 创建稀疏矩阵M */
   int i,m,n;
   ElemType e;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素数：");
   scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
   (*M).data[0].i=0; /* 为以下比较顺序做准备 */
   for(i=1;i<=(*M).tu;i++)
   {
     do
     {
       printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",i,(*M).mu,(*M).nu);
       scanf("%d,%d,%d",&m,&n,&e);
       k=0;
       if(m<1||m>(*M).mu||n<1||n>(*M).nu) /* 行或列超出范围 */
         k=1;
       if(m<(*M).data[i-1].i||m==(*M).data[i-1].i&&n<=(*M).data[i-1].j) /* 行或列的顺序有错 */
         k=1;
     }while(k);
     (*M).data[i].i=m;
     (*M).data[i].j=n;
     (*M).data[i].e=e;
   }
   return OK;
 }

 void DestroySMatrix(TSMatrix *M)
 { /* 销毁稀疏矩阵M */
   (*M).mu=0;
   (*M).nu=0;
   (*M).tu=0;
 }

 void PrintSMatrix(TSMatrix M)
 { /* 输出稀疏矩阵M */
   int i;
   printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
   printf("行  列  元素值\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
 }

 Status CopySMatrix(TSMatrix M,TSMatrix *T)
 { /* 由稀疏矩阵M复制得到T */
   (*T)=M;
   return OK;
 }

 int comp(int c1,int c2) /* 另加 */
 { /* AddSMatrix函数要用到 */
   int i;
   if(c1<c2)
     i=1;
   else if(c1==c2)
     i=0;
   else
     i=-1;
   return i;
 }

 Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的和Q=M+N */
   Triple *Mp,*Me,*Np,*Ne,*Qh,*Qe;
   if(M.mu!=N.mu)
     return ERROR;
   if(M.nu!=N.nu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=M.nu;
   Mp=&M.data[1]; /* Mp的初值指向矩阵M的非零元素首地址 */
   Np=&N.data[1]; /* Np的初值指向矩阵N的非零元素首地址 */
   Me=&M.data[M.tu]; /* Me指向矩阵M的非零元素尾地址 */
   Ne=&N.data[N.tu]; /* Ne指向矩阵N的非零元素尾地址 */
   Qh=Qe=(*Q).data; /* Qh、Qe的初值指向矩阵Q的非零元素首地址的前一地址 */
   while(Mp<=Me&&Np<=Ne)
   {
     Qe++;
     switch(comp(Mp->i,Np->i))
     {
       case  1: *Qe=*Mp;
                Mp++;
                break;
       case  0: switch(comp(Mp->j,Np->j)) /* M、N矩阵当前非零元素的行相等,继续比较列 */
                {
                  case  1: *Qe=*Mp;
                           Mp++;
                           break;
                  case  0: *Qe=*Mp;
                           Qe->e+=Np->e;
                           if(!Qe->e) /* 元素值为0，不存入压缩矩阵 */
                             Qe--;
                           Mp++;
                           Np++;
                           break;
                  case -1: *Qe=*Np;
                           Np++;
                }
                break;
       case -1: *Qe=*Np;
                Np++;
     }
   }
   if(Mp>Me) /* 矩阵M的元素全部处理完毕 */
     while(Np<=Ne)
     {
       Qe++;
       *Qe=*Np;
       Np++;
     }
   if(Np>Ne) /* 矩阵N的元素全部处理完毕 */
     while(Mp<=Me)
     {
       Qe++;
       *Qe=*Mp;
       Mp++;
     }
   (*Q).tu=Qe-Qh; /* 矩阵Q的非零元素个数 */
   return OK;
 }

 Status SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的差Q=M-N */
   int i;
   for(i=1;i<=N.tu;i++)
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q);
   return OK;
 }

 Status MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的乘积Q=M*N */
   int i,j,h=M.mu,l=N.nu,Qn=0;
   /* h,l分别为矩阵Q的行、列值,Qn为矩阵Q的非零元素个数，初值为0 */
   ElemType *Qe;
   if(M.nu!=N.mu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=N.nu;
   Qe=(ElemType *)malloc(h*l*sizeof(ElemType)); /* Qe为矩阵Q的临时数组 */
   /* 矩阵Q的第i行j列的元素值存于*(Qe+(i-1)*l+j-1)中，初值为0 */
   for(i=0;i<h*l;i++)
     *(Qe+i)=0; /* 赋初值0 */
   for(i=1;i<=M.tu;i++) /* 矩阵元素相乘，结果累加到Qe */
     for(j=1;j<=N.tu;j++)
       if(M.data[i].j==N.data[j].i)
         *(Qe+(M.data[i].i-1)*l+N.data[j].j-1)+=M.data[i].e*N.data[j].e;
   for(i=1;i<=M.mu;i++)
     for(j=1;j<=N.nu;j++)
       if(*(Qe+(i-1)*l+j-1)!=0)
       {
         Qn++;
         (*Q).data[Qn].e=*(Qe+(i-1)*l+j-1);
         (*Q).data[Qn].i=i;
         (*Q).data[Qn].j=j;
       }
   free(Qe);
   (*Q).tu=Qn;
   return OK;
 }

 Status TransposeSMatrix(TSMatrix M,TSMatrix *T)
 { /* 求稀疏矩阵M的转置矩阵T。算法5.1 */
   int p,q,col;
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     q=1;
     for(col=1;col<=M.nu;++col)
       for(p=1;p<=M.tu;++p)
         if(M.data[p].j==col)
         {
           (*T).data[q].i=M.data[p].j;
           (*T).data[q].j=M.data[p].i;
           (*T).data[q].e=M.data[p].e;
           ++q;
         }
   }
   return OK;
 }

 Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T)
 { /* 快速求稀疏矩阵M的转置矩阵T。算法5.2 */
   int p,q,t,col,*num,*cpot;
   num=(int *)malloc((M.nu+1)*sizeof(int)); /* 生成数组（[0]不用） */
   cpot=(int *)malloc((M.nu+1)*sizeof(int)); /* 生成数组（[0]不用） */
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     for(col=1;col<=M.nu;++col)
       num[col]=0; /* 设初值 */
     for(t=1;t<=M.tu;++t) /* 求M中每一列含非零元素个数 */
       ++num[M.data[t].j];
     cpot[1]=1;
     for(col=2;col<=M.nu;++col) /* 求第col列中第一个非零元在(*T).data中的序号 */
       cpot[col]=cpot[col-1]+num[col-1];
     for(p=1;p<=M.tu;++p)
     {
       col=M.data[p].j;
       q=cpot[col];
       (*T).data[q].i=M.data[p].j;
       (*T).data[q].j=M.data[p].i;
       (*T).data[q].e=M.data[p].e;
       ++cpot[col];
     }
   }
   free(num);
   free(cpot);
   return OK;
 }

 void main()
 {
   TSMatrix A,B;
   printf("创建矩阵A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   FastTransposeSMatrix(A,&B);
   printf("矩阵B(A的快速转置): ");
   PrintSMatrix(B);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
 }
 
typedef int SElemType; /* 定义栈元素类型 */
 #define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
 #define STACKINCREMENT 2 /* 存储空间分配增量 */
 typedef struct SqStack
 {
   SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
   SElemType *top; /* 栈顶指针 */
   int stacksize; /* 当前已分配的存储空间，以元素为单位 */
 }SqStack; /* 顺序栈 */
 
 Status InitStack(SqStack *S)
 { /* 构造一个空栈S */
   (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   if(!(*S).base)
     exit(OVERFLOW); /* 存储分配失败 */
   (*S).top=(*S).base;
   (*S).stacksize=STACK_INIT_SIZE;
   return OK;
 }

 Status DestroyStack(SqStack *S)
 { /* 销毁栈S，S不再存在 */
   free((*S).base);
   (*S).base=NULL;
   (*S).top=NULL;
   (*S).stacksize=0;
   return OK;
 }

 Status ClearStack(SqStack *S)
 { /* 把S置为空栈 */
   (*S).top=(*S).base;
   return OK;
 }

 Status StackEmpty(SqStack S)
 { /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
   if(S.top==S.base)
     return TRUE;
   else
     return FALSE;
 }

 int StackLength(SqStack S)
 { /* 返回S的元素个数，即栈的长度 */
   return S.top-S.base;
 }

 Status GetTop(SqStack S,SElemType *e)
 { /* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
   if(S.top>S.base)
   {
     *e=*(S.top-1);
     return OK;
   }
   else
     return ERROR;
 }

 Status Push(SqStack *S,SElemType e)
 { /* 插入元素e为新的栈顶元素 */
   if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */
   {
     (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
     if(!(*S).base)
       exit(OVERFLOW); /* 存储分配失败 */
     (*S).top=(*S).base+(*S).stacksize;
     (*S).stacksize+=STACKINCREMENT;
   }
   *((*S).top)++=e;
   return OK;
 }

 Status Pop(SqStack *S,SElemType *e)
 { /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
   if((*S).top==(*S).base)
     return ERROR;
   *e=*--(*S).top;
   return OK;
 }

 Status StackTraverse(SqStack S,Status(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   /* 一旦visit()失败，则操作失败 */
   while(S.top>S.base)
     visit(*S.base++);
   printf("\n");
   return OK;
 }

 Status visit(SElemType c)
 {
   printf("%d ",c);
   return OK;
 }

 void main()
 {
   int j;
   SqStack s;
   SElemType e;
   if(InitStack(&s)==OK)
     for(j=1;j<=12;j++)
       Push(&s,j);
   printf("The ElemType in this status are:");
   StackTraverse(s,visit);
   Pop(&s,&e);
   printf("the pop ElemType is e=%d\n",e);
   printf("empty or not:%d(1:empty 0:not empty)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("The top ElemType is e=%d  The length of status is %d\n",e,StackLength(s));
   ClearStack(&s);
   printf("After clear the status,empty or not:%d(1:empty 0:not empty)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("After destory the status,s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
 }
 
typedef int QElemType;
 /* 单链队列－－队列的链式存储结构 */
 typedef struct QNode
 {
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

 typedef struct
 {
   QueuePtr front,rear; /* 队头、队尾指针 */
 }LinkQueue;

  /*  链队列(存储结构定义)的基本操作(9个) */
 Status InitQueue(LinkQueue *Q)
 { /* 构造一个空队列Q */
   (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
   if(!(*Q).front)
     exit(OVERFLOW);
   (*Q).front->next=NULL;
   return OK;
 }

 Status DestroyQueue(LinkQueue *Q)
 { /* 销毁队列Q(无论空否均可) */
   while((*Q).front)
   {
     (*Q).rear=(*Q).front->next;
     free((*Q).front);
     (*Q).front=(*Q).rear;
   }
   return OK;
 }

 Status ClearQueue(LinkQueue *Q)
 { /* 将Q清为空队列 */
   QueuePtr p,q;
   (*Q).rear=(*Q).front;
   p=(*Q).front->next;
   (*Q).front->next=NULL;
   while(p)
   {
     q=p;
     p=p->next;
     free(q);
   }
   return OK;
 }

 Status QueueEmpty(LinkQueue Q)
 { /* 若Q为空队列,则返回TRUE,否则返回FALSE */
   if(Q.front==Q.rear)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(LinkQueue Q)
 { /* 求队列的长度 */
   int i=0;
   QueuePtr p;
   p=Q.front;
   while(Q.rear!=p)
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetHead_Q(LinkQueue Q,QElemType *e) 
 { /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
   QueuePtr p;
   if(Q.front==Q.rear)
     return ERROR;
   p=Q.front->next;
   *e=p->data;
   return OK;
 }

 Status EnQueue(LinkQueue *Q,QElemType e)
 { /* 插入元素e为Q的新的队尾元素 */
   QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
   if(!p) /* 存储分配失败 */
     exit(OVERFLOW);
   p->data=e;
   p->next=NULL;
   (*Q).rear->next=p;
   (*Q).rear=p;
   return OK;
 }

 Status DeQueue(LinkQueue *Q,QElemType *e)
 { /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
   QueuePtr p;
   if((*Q).front==(*Q).rear)
     return ERROR;
   p=(*Q).front->next;
   *e=p->data;
   (*Q).front->next=p->next;
   if((*Q).rear==p)
     (*Q).rear=(*Q).front;
   free(p);
   return OK;
 }

 Status QueueTraverse(LinkQueue Q,void(*vi)(QElemType))
 { /* 从队头到队尾依次对队列Q中每个元素调用函数vi()。一旦vi失败,则操作失败 */
   QueuePtr p;
   p=Q.front->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   int i;
   QElemType d;
   LinkQueue q;
   i=InitQueue(&q);
   if(i)
     printf("InitQueue success!\n");
   printf("Queue empty or not?%d(1:empty 0:not empty)  ",QueueEmpty(q));
   printf("The length of Queue is %d\n",QueueLength(q));
   EnQueue(&q,-5);
   EnQueue(&q,5);
   EnQueue(&q,10);
   printf("After insert(-5,5,10),The length of Queue is %d\n",QueueLength(q));
   printf("Queue empty or not?%d(1:empty 0:not empty)  ",QueueEmpty(q));
   printf("Output the Queue in term is:");
   QueueTraverse(q,visit);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("The front of Queue is: %d\n",d);
   DeQueue(&q,&d);
   printf("After delete the front ElemType%d\n",d);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("The new front of Queue is: %d\n",d);
   ClearQueue(&q);
   printf("After clear the Queue,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
   DestroyQueue(&q);
   printf("After destory the Queue,q.front=%u q.rear=%u\n",q.front, q.rear);
 } 
