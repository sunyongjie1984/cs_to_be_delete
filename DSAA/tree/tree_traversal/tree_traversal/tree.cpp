// 树的遍历

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

#define MAX_CNT 5
#define BASE  100

int main(int argc, char *argv[])
{
    int i;
    pTreeT root = NULL;

    srand((unsigned)time( NULL ));

    for (i=0; i<MAX_CNT; i++)
    {
        BT_Insert(rand() % BASE, &root);
    }

    //前序
    printf("PreOrder:\n");
    BT_PreOrder(root);
    printf("\n");

    printf("PreOrder no recursion:\n");
    BT_PreOrderNoRec(root);
    printf("\n");

    //中序
    printf("InOrder:\n");
    BT_InOrder(root);
    printf("\n");

    printf("InOrder no recursion:\n");
    BT_InOrderNoRec(root);
    printf("\n");

    //后序
    printf("PostOrder:\n");
    BT_PostOrder(root);
    printf("\n");

    //层序
    printf("LevelOrder:\n");
    BT_LevelOrder(root);
    printf("\n");

    std::cin.get();
    return 0;
}
