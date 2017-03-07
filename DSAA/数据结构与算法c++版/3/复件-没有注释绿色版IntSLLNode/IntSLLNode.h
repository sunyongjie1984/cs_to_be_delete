#ifndef INT_SINGLY_LINKED_LIST_NODE
#define INT_SINGLY_LINKED_LIST_NODE
class IntSLLNode {
public:
	IntSLLNode() 
	{
		next = 0; // 为什么不用NULL
	}
	IntSLLNode(int i, IntSLLNode *in = 0)
	{
		info = i;
		next = in;
	}
	int info;
	IntSLLNode *next;
};
#endif
