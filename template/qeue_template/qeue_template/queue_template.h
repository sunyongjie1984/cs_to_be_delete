template <class Type>
class QueueItem {
public:
	QueueItem() : item (0), next (0)
	{

	}
private:
	Type item;
	QueueItem* next;
};

template <class Type>
class Queue {
public:
	Queue() : front (0), back (0) 
	{

	}
	~Queue()
	{
		while (!is_empty())
		{
			remove();
		}
	}
	Type& remove();

	void add(const Type&);
	bool is_empty()
	{
		return 0 == front;
	}
private:
	QueueItem<Type>* front;
	QueueItem<Type>* back;
};
