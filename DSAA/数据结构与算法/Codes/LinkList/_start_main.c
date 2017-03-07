#include "LinkList.h"

int main(int argc, char * argv[])
{	
	LINK_LIST * pListHead = NULL;
	LINK_LIST Node;

	int loop;

	char str[__LEN_32];

	printf("start linklist!\r\n");	

	CreateListHead(&pListHead);
	
	for (loop = 0; loop < 5; loop++)
	{
		memset(&Node, 0, sizeof(LINK_LIST));
		memset(str, 0, sizeof(str));
		sprintf(str, "add %d", loop);
		strcpy(Node.data_type.str, str);

		AddListLastNode(pListHead, &Node);
	}
	memset(&Node, 0, sizeof(LINK_LIST));
	memset(str, 0, sizeof(str));
	sprintf(str, "add %d", 9);
	strcpy(Node.data_type.str, str);
	
	InsertListNode(pListHead, 3, &Node);

	FreeListMember(pListHead);

	FreeListAll(pListHead);
	
	return __SUCCESS;
}