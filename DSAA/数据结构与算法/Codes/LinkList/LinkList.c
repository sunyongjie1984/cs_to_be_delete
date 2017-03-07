#include "LinkList.h"

int CreateListHead(LINK_LIST ** pListHead)
{
	*pListHead = (PLINK_LIST)malloc(sizeof(LINK_LIST));

	if (*pListHead)
	{		
		memset(*pListHead, 0, sizeof(LINK_LIST));

		return __SUCCESS;
	}
	return __FAIDED;
}

int FreeListAll(LINK_LIST * pListHead)
{
	LINK_LIST * pT = NULL;

	if (NULL == pListHead)
	{
		return __FAIDED;
	}
	while (pListHead)
	{
		pT = pListHead;

		pListHead = pListHead->pNext;

#ifdef __DEBUG_CODE
	printf("\r\nFreeListAll : pT = %x pListHead = %x pT->data_type.str = %s\r\n",
			pT, pListHead, pT->data_type.str);
#endif//__DEBUG_CODE
		
		free(pT);
			
		pT = NULL;
	}
	return __FAIDED;
}

int FreeListMember(LINK_LIST * pListHead)
{
	LINK_LIST * pT = NULL;

	if (NULL == pListHead)
	{
		return __FAIDED;
	}
	while (pListHead->pNext)
	{
		pT = pListHead->pNext;

		if (pT)
		{
			pListHead->pNext = pT->pNext;

			(pListHead->len)--;

#ifdef __DEBUG_CODE
	printf("\r\nFreeListMember : pT = %x pListHead->pNext = %x pT->data_type.str = %s pListHead->len = %d\r\n",
			pT, pListHead->pNext, pT->data_type.str, pListHead->len);
#endif//__DEBUG_CODE
			
			free(pT);
			
			pT = NULL;
		}
	}
	return __FAIDED;
}

int AddListLastNode(LINK_LIST * pListHead, LINK_LIST * pDataNode)
{
	LINK_LIST * pT = NULL;
	LINK_LIST * pD = NULL;

	if (NULL == pListHead)
	{
		return __FAIDED;
	}
	pT = pListHead;

	while (pListHead)
	{
		if (pT->pNext)
		{
			pT = pT->pNext;
		}
		else
		{
			pD = (PLINK_LIST)malloc(sizeof(LINK_LIST));

			*pD = *pDataNode;

			pT->pNext = pD;
			
			pD->pNext = NULL;

			(pListHead->len)++;

#ifdef __DEBUG_CODE
	printf("\r\nAddListLastNode : pT = %x pT->pNext = %x pD->data_type.str = %s pListHead->len = %d\r\n",
			pT, pT->pNext, pD->data_type.str, pListHead->len);
#endif//__DEBUG_CODE

			break;
		}
	}
	return __SUCCESS;
}

int InsertListNode(LINK_LIST * pListHead, int postion, LINK_LIST * pDataNode)
{
	LINK_LIST * pN = NULL;
	LINK_LIST * pS = NULL;
	LINK_LIST * pD = NULL;

	int count = -1;

	if (NULL == pListHead)
	{
		return __FAIDED;
	}
	if ( (postion > pListHead->len) || (postion < 1) )
	{
		return __FAIDED;
	}
	pS = pN = pListHead;
	
	while (pS)
	{
		if (count < postion)
		{
			pS = pN;
			pN = pS->pNext;

			count++;

#ifdef __DEBUG_CODE
	printf("\r\nInsertListNode : pS = %x pS->pNext = %x count = %d\r\n",
			pS, pS->pNext, count);
#endif//__DEBUG_CODE

		}
		else
		{
			pD = (PLINK_LIST)malloc(sizeof(LINK_LIST));

			*pD = *pDataNode;

			pS->pNext = pD;

			pD->pNext = pN;

			pListHead->len++;

#ifdef __DEBUG_CODE
	printf("\r\nInsertListNode : pS = %x pS->pNext = %x pN = %x pListHead->len = %d\r\n",
			pS, pS->pNext, pN, pListHead->len);
#endif//__DEBUG_CODE
			
			return __SUCCESS;
		}
	}
	return __FAIDED;
}

int DeleteListNode(LINK_LIST * pListHead, int postion)
{
	LINK_LIST * pN = NULL;
	LINK_LIST * pS = NULL;
	LINK_LIST * pF = NULL;
	
	int count = 0;
	
	if (NULL == pListHead)
	{
		return __FAIDED;
	}
	if ( (postion > pListHead->len) || (postion < 1) )
	{
		return __FAIDED;
	}
	pS = pN = pListHead;
	
	while (pS)
	{
		if (count < postion)
		{
			pS = pN;
			pN = pS->pNext;
			
			count++;
			
#ifdef __DEBUG_CODE
			printf("\r\nDeleteListNode : pS = %x pS->pNext = %x count = %d\r\n",
				pS, pS->pNext, count);
#endif//__DEBUG_CODE
			
		}
		else
		{
			pF = pN;

			pS->pNext = pN->pNext;

			free(pF);

			pF = NULL;

			pListHead->len--;

#ifdef __DEBUG_CODE
			printf("\r\nDeleteListNode : pS = %x pS->pNext = %x pN = %x pListHead->len = %d\r\n",
				pS, pS->pNext, pN, pListHead->len);
#endif//__DEBUG_CODE

			return __SUCCESS;
		}
	}
	return __FAIDED;
}

int GetListNode(LINK_LIST * pListHead, int postion, LINK_LIST * pDataNode)
{
	return __FAIDED;
}

int SetListNode(LINK_LIST * pListHead, int postion, LINK_LIST * pDataNode)
{
	return __FAIDED;
}