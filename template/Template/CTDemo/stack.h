template <class T, int nMaxSize>
class Stack  
{
// methods
public:
	// store the itme on the top of the stack
	void Push(const T& item)
	{
		if (top == nMaxSize-1)
		{
			cerr << "Stack overflow!" << endl;
			exit(1);
		}

		top++;
		stackList[top] = item;
	}

	// remove the item from the top of the stack
	T Pop()
	{
		T temp;

		if (top == -1)
		{
			cerr << "Attempt to pop an empty stack!" << endl;
			exit(1);
		}
		
		temp = stackList[top];

		top--;
		return temp;
	}

	// check wether the stack is empty
	int StackEmpty() const
	{
		return top == -1;
	}

	// constructor
	Stack(void)
	{
		top = -1;
	}

// variables
private:
	int  top;
	T stackList[nMaxSize];
};

