#include <iostream>
#include "sq_list.h"

#ifdef __linux
#include <stdlib.h>
#include <stdio.h>
#endif

int initList_sq(SqList& list)
{
    list.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
    list.length = 0;
    list.listsize = LIST_INIT_SIZE;
    return 0;
}

int listInsert_sq(SqList& list, int i, int e)
{
    if(i < 1 || i > list.length+1)
        return 0;
    if(list.length >= list.listsize)
    {
        int* relem = (int*)realloc(list.elem, (list.listsize + LISTINCREMENT) * sizeof(int));
        list.elem = relem;
        list.listsize += LISTINCREMENT;
    }

    int* q = &(list.elem[i-1]);
    for(int* p = &(list.elem[list.length - 1]); p >= q; --p)
    {
        *(p + 1) = *p;
    }
    *q = e;
    ++list.length;
    return 0;
}

int main()
{

    SqList sq;
    initList_sq(sq);
    sq.elem[0] = 10;
    sq.elem[1] = 20;
    sq.length = 2;
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 30);
    listInsert_sq(sq, 3, 100);
    std::cout << sq.elem[2] << std::endl;
    std::cout << sq.elem[19] << std::endl;

    getchar();
    return 0;

}
