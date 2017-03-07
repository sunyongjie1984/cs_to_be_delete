#include "QueueItem.h"
template <class Type> class Queue {
public:
	// empty queue
	Queue() : head(0), tail(0) { }
	// copy control to manage pointers to QueueItems in the Queue
	Queue(const Queue& Q) : head(0), tail(0)
	{
		copy_elems(Q);
	}
	~Queue() { destroy(); }
	// return element from head of Queue
	// unchecked operation: front on an empty Queue is undefined
	Type& front() { return head->item; }
	const Type& front() const { return head->item; }
	void push(const Type&); // add element to back of Queue
	void pop();             // remove element from head of Queue
	bool empty() const { return head == 0; }
private:
	QueueItem<Type>* head; // pointer to first item of the queue
	QueueItem<Type>* tail; // pointer to last item of the queue
	// utility functions used by copy constructor, assignment
	// ,and destructor
	void destroy(); // delete all elements
	void copy_elems(const Queue&); // copy elements from parameter
};
template<class Type> void Queue<Type>::destroy()
{
	while (!empty())
		pop();
}
template<class Type> void Queue<Type>::pop()
{
	// pop is unchecked: popping off an empty Queue is undefined
	QueueItem<Type>* p = head;
	head = head->next;
	delete p;
}
template<class Type> void Queue<Type>::push(const Type& val)
{
	// allocate a new QueueItem object
	QueueItem<Type>* pt = new QueueItem<Type>(val);
	// put item onto existing queue
	if (empty())
		head = tail = pt;
	else
	{
		tail->next = pt;
		tail = pt;
	}
}
template<class Type> void Queue<Type>::copy_elems(const Queue& orig)
{
	// copy elements from orig into this Queue
	// loop stops when pt == 0, which happens when we reach orig.tail
	for (QueueItem<Type>* pt = orig.head; pt; pt = pt->next)
		push(pt->item);
}
