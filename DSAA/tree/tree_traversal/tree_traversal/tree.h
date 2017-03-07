/********************************************************************
created:    2005/12/30
created:    30:12:2005   10:39
filename:     bintree.h
author:        Liu Qi

purpose:    二叉树的3种遍历方式(包括非递归实现),前序，后序和中序，先访问根节点就是
前序(部分书籍称为先根遍历,个人觉得该说法更好^_^)，类似的，最后访问根节点就是后序
*********************************************************************/

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>
#include <assert.h>

using namespace std;

typedef int ElemType;

typedef struct treeT
{
    ElemType key;
    struct treeT* left;
    struct treeT* right;
}treeT, *pTreeT;

/*===========================================================================
* Function name:    visit
* Parameter:        root:树根节点指针
* Precondition:
* Description:
* Return value:
* Author:            Liu Qi, //
===========================================================================*/
static void visit(pTreeT root)
{
    if (NULL != root)
    {
        printf(" %d\n", root->key);
    }
}

/*===========================================================================
* Function name:  BT_MakeNode
* Parameter:      target:元素值
* Precondition:      None
* Postcondition:  NULL != pTreeT 
* Description:      构造一个tree节点，置左右指针为空，并且返回指向新节点的指针
* Return value:      指向新节点的指针
* Author:            Liu Qi,  [12/30/2005]
===========================================================================*/
static pTreeT BT_MakeNode(ElemType target)
{
    pTreeT pNode = (pTreeT) malloc(sizeof(treeT));

    assert( NULL != pNode );

    pNode->key   = target;
    pNode->left  = NULL;
    pNode->right = NULL;

    return pNode;
}

/*===========================================================================
* Function name:    BT_Insert
* Parameter:        target:要插入的元素值, pNode:指向某一个节点的指针
* Precondition:         NULL != ppTree 
* Description:        插入target到pNode的后面
* Return value:        指向新节点的指针
* Author:            Liu Qi,  [12/29/2005]
===========================================================================*/
pTreeT BT_Insert(ElemType target, pTreeT* ppTree)
{
    pTreeT Node;

    assert( NULL != ppTree ); 

    Node = *ppTree;
    if (NULL == Node)
    {
        return *ppTree = BT_MakeNode(target);
    }

    if (Node->key == target)    //不允许出现相同的元素
    {
        return NULL;
    }
    else if (Node->key > target)    //向左
    {
        return BT_Insert(target, &Node->left);
    }
    else
    {
        return BT_Insert(target, &Node->right);
    }
}

/*===========================================================================
* Function name:    BT_PreOrder
* Parameter:        root:树根节点指针
* Precondition:        None
* Description:        前序遍历
* Return value:        void
* Author:            Liu Qi,  [12/29/2005]
===========================================================================*/
void BT_PreOrder(pTreeT root)
{
    if (NULL != root)
    {
        visit(root);
        BT_PreOrder(root->left);
        BT_PreOrder(root->right);
    }
}

/*===========================================================================
* Function name:    BT_PreOrderNoRec
* Parameter:        root:树根节点指针
* Precondition:        Node
* Description:        前序(先根)遍历非递归算法
* Return value:        void
* Author:            Liu Qi,  [1/1/2006]
===========================================================================*/
void BT_PreOrderNoRec(pTreeT root)
{
    stack<treeT *> s;

    while ((NULL != root) || !s.empty())
    {
        if (NULL != root)
        {
            visit(root);
            s.push(root);
            root = root->left;
        }
        else
        {
            root = s.top();
            s.pop();
            root = root->right;
        }
    }
}

/*===========================================================================
* Function name:    BT_InOrder
* Parameter:        root:树根节点指针
* Precondition:        None
* Description:        中序遍历
* Return value:        void
* Author:            Liu Qi,  [12/30/2005]
===========================================================================*/
void BT_InOrder(pTreeT root)
{
    if (NULL != root)
    {
        BT_InOrder(root->left);
        visit(root);
        BT_InOrder(root->right);
    }
}

/*===========================================================================
* Function name:    BT_InOrderNoRec
* Parameter:        root:树根节点指针
* Precondition:        None
* Description:        中序遍历,非递归算法
* Return value:        void
* Author:            Liu Qi,  [1/1/2006]
===========================================================================*/
void BT_InOrderNoRec(pTreeT root)
{
    stack<treeT *> s;
    while ((NULL != root) || !s.empty())
    {
        if (NULL != root)
        {
            s.push(root);
            root = root->left;
        }
        else
        {
            root = s.top();
            visit(root);
            s.pop();
            root = root->right;
        }
    }
}

/*===========================================================================
* Function name:    BT_PostOrder
* Parameter:        root:树根节点指针
* Precondition:        None
* Description:        后序遍历
* Return value:        void
* Author:            Liu Qi,  [12/30/2005]
===========================================================================*/
void BT_PostOrder(pTreeT root)
{
    if (NULL != root)
    {
        BT_PostOrder(root->left);
        BT_PostOrder(root->right);
        visit(root);
    }
}

/*===========================================================================
* Function name:    BT_PostOrderNoRec
* Parameter:        root:树根节点指针
* Precondition:        None
* Description:        后序遍历,非递归算法
* Return value:        void
* Author:            Liu Qi, //  [1/1/2006]
===========================================================================*/
void BT_PostOrderNoRec(pTreeT root)
{
    //学习中，尚未明白
}

/*===========================================================================
* Function name:    BT_LevelOrder
* Parameter:        root:树根节点指针
* Precondition:        NULL != root
* Description:        层序遍历
* Return value:        void
* Author:            Liu Qi,  [1/1/2006]
===========================================================================*/
void BT_LevelOrder(pTreeT root)
{
    queue<treeT *> q;
    treeT *treePtr;

    assert( NULL != root ); 

    q.push(root);

    while (!q.empty())
    {
        treePtr = q.front();
        q.pop();
        visit(treePtr);

        if (NULL != treePtr->left)
        {
            q.push(treePtr->left);
        }
        if (NULL != treePtr->right)
        {
            q.push(treePtr->right);
        }

    }
}

#endif

