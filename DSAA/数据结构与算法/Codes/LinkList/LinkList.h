#ifndef	__LINK_LIST_H_
#define	__LINK_LIST_H_

#include "stdio.h"

#endif//__LINK_LIST_H_
#define __DEBUG_CODE

#define __SUCCESS	0
#define __FAIDED	-1

#define __LEN_32	32

typedef struct _DATA_TYPE
{
	char str[__LEN_32];
}
DATA_TYPE, * PDATA_TYPE;

typedef struct _LINK_LIST
{
	struct _LINK_LIST * pNext;
	int					len;
	DATA_TYPE			data_type;
}
LINK_LIST, * PLINK_LIST;

int CreateListHead(LINK_LIST ** pListHead);
int FreeListAll(LINK_LIST * pListHead);

int AddListLastNode(LINK_LIST * pListHead, LINK_LIST * pDataNode);
int AddListFrontNode(LINK_LIST * pListHead, LINK_LIST * pDataNode);
int InsertListNode(LINK_LIST * pListHead, int postion, LINK_LIST * pDataNode);
int DeleteListNode(LINK_LIST * pListHead, int postion);
int FreeListMember(LINK_LIST * pListHead);

int GetListNode(LINK_LIST * pListHead, int postion, LINK_LIST * pDataNode);
int SetListNode(LINK_LIST * pListHead, int postion, LINK_LIST * pDataNode);

typedef struct _QUEUE_NODE
{
	struct _QUEUE_NODE * pNext;
	DATA_TYPE			 data_type;
}
QUEUE_NODE, * PQUEUE_NODE;

typedef struct _QUEUE
{
	PQUEUE_NODE pFront;
	PQUEUE_NODE pLast;
}
QUEUE, * PQUEUE;

int	InitializeQueue(QUEUE &queue);

int WriteQueueNode(QUEUE &queue, QUEUE_NODE * qNode);
int ReadQueueNode(QUEUE &queue, QUEUE_NODE * qNode);

int ClearQueueMember(QUEUE &queue);