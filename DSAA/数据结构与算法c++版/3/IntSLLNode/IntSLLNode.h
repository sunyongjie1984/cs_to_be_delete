#ifndef INT_SINGLY_LINKED_LIST_NODE
#define INT_SINGLY_LINKED_LIST_NODE
class IntSLLNode 
{
public:
	IntSLLNode() 
	{
		next = 0; // 这是一个保险。啊 
	}
	IntSLLNode(int i, IntSLLNode *in = 0)
	{
		info = i;
		next = in; // 两个构造函数都将next置了0,太有用了
	}
	int info;
	IntSLLNode *next; // 我今后想把它们都写成IntSLLNode* next;
};                    // 不知道好不好，我觉得更容易理解
#endif                // 因为IntSLLNode* 是next的类型名
