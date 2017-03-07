// MyStack.cpp: implementation of the MyStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyStack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 
// 
// 
// template<class T>
// MyStack<T>::MyStack(size_t size )
// :m_impl(size)
// {
// 
// }
// 
// template<class T>
// MyStack<T>::~MyStack()
// {
// 	
// }
// template<class T>
// MyStack<T>::MyStack(const MyStack& other)
// :m_impl(other.m_impl.m_vUsed)
// {
// 	while(m_impl.m_vUsed < other.m_impl.m_vUsed)
// 	{
// 		construct(m_impl.m_v + m_impl.m_vUsed, other.m_impl[m_impl.m_vUsed]);
// 		++m_impl.m_vUsed;
// 	}
// }
// template<class T>
// MyStack<T>& MyStack<T>::operator=(const MyStack& other)
// {
// 	MyStack<T> temp(other);
// 	m_impl.Swap(temp.m_impl);
// 	return *this;
// }
// template<class T>
// void MyStack<T>::Push(const T& t)
// {
// 	if(m_impl.m_vUsed == m_impl.m_vSize)
// 	{
// 		MyStack<T> temp(m_impl.m_vSize * 2 + 1);
// 		while(temp.count() < m_impl.m_vUsed)
// 		{
// 			temp.Push(m_impl.m_v[temp.count()]);
// 		}
// 		temp.Push(t);
// 		m_impl.Swap(temp.m_impl);
// 	}
// 	else{
// 		construct(m_impl.m_v + m_impl.m_vUsed, t);
// 		++m_impl.m_vUsed;
// 	}
// }
// template<class T>
// size_t MyStack<T>::count() const
// {
// 	return m_impl.m_vUsed;
// }
// template<class T>
// T& MyStack<T>::Top()
// {
// 	if(m_impl.m_vUsed == 0)
// 	{
// 		throw "empty stack";
// 	}
// 	return m_impl.m_v[m_impl.m_vUsed - 1];
// }
// template<class T>
// void MyStack<T>::Pop()
// {
// 	if( m_impl.m_vUsed == 0)
// 	{
// 		throw "Pop from empty stack";
// 	}
// 	else
// 	{
// 		--m_impl.m_vUsed;
// 		destroy(m_impl.m_v + m_impl.m_vUsed);
// 	}
// }