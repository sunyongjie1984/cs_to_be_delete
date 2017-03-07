#include <iostream>
#include "LNode.h"

#ifdef __linux
#include <stdio.h>
#include <stdlib.h>
#endif

void CreateList_L(LinkList& L, const int n){
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = n; i > 0; --i)
    {
        LinkList p = (LinkList)malloc(sizeof(LNode));
        //scanf(&p->data);
        std::cin >> p->data;

        p->next = L->next;
        L->next = p;
    }

}

void CreateList_L_from_end(LinkList& L, const int n)
{
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;

    LinkList p = L;
    for (int i = n; i > 0; --i)
    {
        LinkList s = (LinkList)malloc(sizeof(LNode));
        std::cin >> s->data;
        p->next = s;
        p=s;
    }
    p->next = NULL;
}

void DestroyList(LinkList pL)
{
    LinkList r = pL->next;
    LinkList q = r->next;
    while(NULL != r->next)
    {
        free(r);
        r = q;
        q = q->next;
    }
}


void PrintList_L(LinkList pL)
{
    pL = pL->next;
    while(NULL != pL)
    {
        std::cout << pL->data << " ";
        pL = pL->next;
    }
}

int LocateElement_L(LinkList L, ElemType x)
{
    int i = 0;
    LinkList q = L->next;
    while (NULL != q && q->data != x)
    {
        q = q->next;
        i++;
    }
    if (NULL == q)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

void MergeList_L(LinkList& La, LinkList& Lb, LinkList& Lc)
{
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    LinkList pc = La;
    Lc = pc;

    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}

int main ()
{
    LinkList L;

    CreateList_L(L, 3);
    std::cout << "list 1:" << std::endl;
    PrintList_L(L);
    std::cout << std::endl;

    LinkList L2;
    //  CreateList_L_from_end
    CreateList_L_from_end(L2, 3);
    std::cout << "list 2:" << std::endl;
    PrintList_L(L2);
    std::cout << std::endl;

    LinkList L3;
    MergeList_L(L, L2, L3);
    PrintList_L(L3);

    // is 30 in the list?
    // locateElement_L
    //int location = LocateElement_L(L, 30);
    //if (-1 != location)
    //{
    //    std::cout << "30 is in the list of number: " << location << std::endl;
    //}
    //else
    //{
    //    std::cout << "30 is not in the list" << std::endl;
    //}
    //DestroyList(L);


    getchar();
    return 0;
}
