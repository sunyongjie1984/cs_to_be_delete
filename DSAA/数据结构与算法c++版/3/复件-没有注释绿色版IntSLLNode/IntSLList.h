#ifndef INT_SINGLY_LINKED_LIST
#define INT_SINGLY_LINKED_LIST
#include "IntSLLNode.h"
class IntSLList {
public:
	IntSLList() 
	{
		head = 0, tail = 0;
	}
	~IntSLList();
	int isEmpty()
	{
		return head == 0;
	}

	void addToHead(int);
	void addtoTail(int);
	
	int deleteFromHead();
	int deleteFromTail();

	void deleteNode(int);

	bool isInList(int) const;

private:
	IntSLLNode *head, *tail;
};
#endif
