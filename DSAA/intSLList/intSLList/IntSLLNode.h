#ifndef INT_SINGLY_LINKED_LIST_NODE
#define INT_SINGLY_LINKED_LIST_NODE

#include <iostream>
using namespace std;

class IntSLLNode 
{
public: // 无参，一个参，二个参都有构造函数。
	IntSLLNode() 
	{
		info = 0;
		next = NULL; // 这是一个保险。啊 
	}
	IntSLLNode(int i, IntSLLNode* in = 0)
	{
		info = i;
		next = in; // 两个构造函数都将next置了0，太有用了
	}
	friend class IntSLList; // very important, solve the problem of using private in other class or global function.
	friend istream& operator>>(istream&, IntSLList&); 
	friend ostream& operator<<(ostream&, const IntSLList&);

private:
	int info;
	IntSLLNode* next; 
};                    
#endif
