// template class Queue declaration
// line 5 and line 15 make together are equal to line 8
// both of the two methods is to tell that
// the class Queue<Type> if a friend of class QueueItem<Type>
// template <class Type> class Queue;

// template class defination
template<class Type> class QueueItem {
	// method 1
	// friend class Queue<Type> declaration
	 template<class T> friend class Queue;

	// line 5 and line 15 make together are equal to line 11
	// friend class Queue<Type> declaration
	// friend class Queue<Type>;

	QueueItem(const Type& t) : item(t), next(0) { }
	Type item;
	QueueItem* next;
};
