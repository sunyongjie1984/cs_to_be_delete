#include "queue_template.h"
template <class Type>
void Queue<Type>::add(const Type& val)
{
	QueueItem<Type>* pt = new QueueItem<Type>(val);
	if (is_empty())
	{
		front = back = pt;
	}
	else
	{
		back->next = pt;
		back = pt;
	}
}

template <class Type>
Type& Queue<Type>::remove()
{
	if (is_empty())
	{
		cerr << "remove() on empty queue\n";
		exit(-1);
	}
	QueueItem<Type>* pt = front;
	front = front->next;

	Type retval = pt->item;
	delete pt;
	return retval;
}