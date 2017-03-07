#ifndef __STACK_H_
#endif	__STACK_H_

template<class Type>
class CStack
{
public:
	CStack();
	virtual ~CStack();
public:
	bool IsEmpty();
	bool IsFull();
	bool Push(const Type &item);
	bool Pop(Type &item);
protected:
private:
	enum{__MAX = 10};
	Type m_items[__MAX];
	int	 m_top;
};

template<class Type>
CStack<Type>::CStack()
{
	m_top	= 0;
}

template<class Type>
CStack<Type>::~CStack()
{
}

template<class Type>
bool CStack<Type>::IsEmpty()
{
	return m_top == 0;
}

template<class Type>
bool CStack<Type>::IsFull()
{
	return m_top == __MAX;
}

template<class Type>
bool CStack<Type>::Push(const Type &item)
{
	if (m_top < __MAX)
	{
		m_items[m_top++] = item;
		return true;
	}
	return false;
}

template<class Type>
bool CStack<Type>::Pop(Type &item)
{
	if (m_top > 0)
	{
		item = item[--m_top];
		return true;
	}
	return false;
}