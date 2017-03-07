#ifndef INT_SINGLY_LINKED_LIST
#define INT_SINGLY_LINKED_LIST

#include "IntSLLNode.h"

using namespace std;
class IntSLList {
public:
	IntSLList(); 
	IntSLList(const int & n);
    IntSLList(istream & is); 
	IntSLList(const IntSLList & object); 

	~IntSLList();

	bool isEmpty() const;

	bool addToHead(const int & el);
	bool addtoTail(const int & el);
	
	bool deleteNode(const int & el);
	int deleteFromHead();
	int deleteFromTail();

	bool isInList(const int&) const;

	IntSLLNode* getHead() const;
	IntSLLNode* getTail() const;

	// 反转单链表
	void reverse_list();

	friend ostream& operator<<(ostream&, const IntSLList&);
	friend istream& operator>>(istream&, IntSLList&); 

private:
	IntSLLNode *head;
	IntSLLNode *tail;
};
#endif
