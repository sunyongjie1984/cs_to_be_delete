// MyStack.h: interface for the MyStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTACK_H__A9545D9B_58D1_4D82_9197_D64566CA25F3__INCLUDED_)
#define AFX_MYSTACK_H__A9545D9B_58D1_4D82_9197_D64566CA25F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <new>
template<class T1, class T2>
void construct(T1* p, const T2& value)
{
	new (p) T1 (value);
}
template<class T>
void destroy(T* p)
{
	p->~T();
}

template<class FwdIter>
void destroy(FwdIter first, FwdIter last)
{
	while(first != last)
	{
		destroy(first);
		++first;
	}
}
template<class T>
void Swap(T& a, T&b)
{
	T temp(a);
	a = b;
	b = temp;
}

template<class T>
class MyStack  
{
private:

	class StackImpl
	{
	public:
		StackImpl(size_t size =0)
			:m_v(static_cast<T*>(
			size == 0 ?
			NULL
			: operator new(sizeof(T) * size))),
		m_vSize(size),
		m_vUsed(0)
		{
		}
		virtual ~StackImpl()
		{
			destroy(m_v, m_v + m_vUsed);
			operator delete(m_v);//??
		}
		void Swap(StackImpl& other) throw()
		{
			::Swap(m_v, other.m_v);
			::Swap(m_vSize, other.m_vSize);
			::Swap(m_vUsed, other.m_vUsed);
		}
		T* m_v;
		size_t m_vSize;
		size_t m_vUsed;
	private:
		StackImpl(const StackImpl&);
		StackImpl& operator=(const StackImpl&);
	};
public:
	MyStack(size_t size = 10)
	:m_impl(size)
	{

	}
	virtual ~MyStack()
	{

	}
	MyStack(const MyStack& other)
	:m_impl(other.m_impl.m_vUsed)
	{
		while(m_impl.m_vUsed < other.m_impl.m_vUsed)
		{
			construct(m_impl.m_v + m_impl.m_vUsed, other.m_impl[m_impl.m_vUsed]);
			++m_impl.m_vUsed;
		}
	}
	MyStack& operator=(const MyStack& other)
	{
		MyStack<T> temp(other);
		m_impl.Swap(temp.m_impl);
		return *this;
	}
	void Push(const T& t)
	{
		if(m_impl.m_vUsed == m_impl.m_vSize)
		{
			MyStack<T> temp(m_impl.m_vSize * 2 + 1);
			while(temp.count() < m_impl.m_vUsed)
			{
				temp.Push(m_impl.m_v[temp.count()]);
			}
			temp.Push(t);
			m_impl.Swap(temp.m_impl);
		}
		else{
			construct(m_impl.m_v + m_impl.m_vUsed, t);
			++m_impl.m_vUsed;
		}
	}
	size_t count() const
	{
		return m_impl.m_vUsed;
	}
	T& Top()
	{
		if(m_impl.m_vUsed == 0)
		{
			throw "empty stack";
		}
		return m_impl.m_v[m_impl.m_vUsed - 1];
	}
	void Pop()
	{
		if( m_impl.m_vUsed == 0)
		{
			throw "Pop from empty stack";
		}
		else
		{
			--m_impl.m_vUsed;
			destroy(m_impl.m_v + m_impl.m_vUsed);
		}
	}

private:
	StackImpl m_impl;
};

#endif // !defined(AFX_MYSTACK_H__A9545D9B_58D1_4D82_9197_D64566CA25F3__INCLUDED_)
