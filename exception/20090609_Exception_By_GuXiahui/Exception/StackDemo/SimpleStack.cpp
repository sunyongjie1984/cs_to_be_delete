// SimpleStack.cpp: implementation of the SimpleStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SimpleStack.h"
#include <xutility>
#include "assert.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
template<class T>
SimpleStack<T>::SimpleStack()
:m_v(new T[10]),
m_vSize(10),
m_vUsed(0)
{

}
template<class T>
SimpleStack<T>::~SimpleStack()
{
	delete [] m_v;
	m_v = NULL;
	m_vSize = 0;
	m_vUsed = 0;
}
template<class T>
SimpleStack<T>::SimpleStack(const SimpleStack<T>& rhs)
:m_v(NewCopy(rhs.m_v, rhs.m_vSize, rhs.m_vSize)),
m_vSize(rhs.m_vSize),
m_vUsed(rhs.m_vUsed)
{
	
}
template<class T>
SimpleStack<T>& SimpleStack<T>::operator=(const SimpleStack<T>& rhs)
{
	if( this != &rhs)
	{
		T* temp = NewCopy(rhs.m_v, rhs.m_vSize, rhs.m_vSize);
		delete[] m_v;
		m_v = NULL;
		m_v = temp;
		m_vSize = rhs.m_vSize;
		m_vUsed = rhs.m_vUsed;
	}
	return *this;
}
template<class T>
T* SimpleStack<T>::NewCopy(T* src, size_t srcSize, size_t destSize)
{
	assert(srcSize <= destSize);
	T* dest = new T[destSize];
	try
	{
		std::copy(src, src + srcSize, dest);
	}
	catch (...)
	{
		delete[] dest;
		throw;
	}
	return dest;
}
template<class T>
size_t SimpleStack<T>::Count() const
{
	return m_vUsed;
}
template<class T>
void SimpleStack<T>::Push(const T& t)
{
	if(m_vUsed == m_vSize)
	{
		size_t newSize = m_vSize * 2 + 1;
		T* temp = NewCopy(m_v, m_vSize, newSize);
		delete [] m_v;
		m_v = NULL;
		m_v = temp;
		m_vSize = newSize;
	}
	m_v[m_vUsed] = t;
	++m_vUsed;
}
template<class T>
T SimpleStack<T>::Pop()
{
	if( 0 == m_vUsed )
	{
		throw "Pop from empty stack";
	}
	else
	{
		T result = m_v[m_vUsed - 1];
		--m_vUsed;
		return result;
	}
}
// template<class T>
// void SimpleStack<T>::Pop()
// {
// 	if( 0 == m_vUsed )
// 	{
// 		throw "Pop from empty stack";
// 	}
// 	else
// 	{
// 		--m_vUsed;
// 	}
// }
// template<class T>
// T SimpleStack<T>::Top()
// {
// 	if( 0 == m_vUsed )
// 	{
// 		throw "empty stack";
// 	}
// 	return m_v[m_vUsed - 1];
// 	
// }
