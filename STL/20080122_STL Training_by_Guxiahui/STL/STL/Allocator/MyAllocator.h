// MyAllocator.h: interface for the MyAllocator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYALLOCATOR_H__6AFA1B6E_D5A9_4615_A14A_E5A0C9C65D59__INCLUDED_)
#define AFX_MYALLOCATOR_H__6AFA1B6E_D5A9_4615_A14A_E5A0C9C65D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

template<class T>
inline T* _allocate(ptrdiff_t size, T*)
{
	set_new_handler(0);
	T* tmp = static_cast<T*>(::operator new(static_cast<size_t>(size * sizeof(T))));
	if ( tmp == 0 )
	{
		exit(1);
	}
	return tmp;
}
template<class T>
inline void _deallocate(T* buffer)
{
	::operator delete(buffer);
}
template<class T1, class T2>
inline void _construct(T1* p, const T2& value)
{
	new(p) T1(value);
}
template<class T>
inline void _destroy(T* ptr)
{
	ptr->~T();
}
template<class T>
class MyAllocator  
{
public:
	typedef T    value_type;
	typedef T*   pointer;
	typedef const T* const_pointer;
	typedef T&     reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	template <class U>
	struct rebind
	{
		typedef MyAllocator<U> other;
	};
	pointer allocate( size_type n, const void* hint = 0)
	{
		return _allocate(static_cast<difference_type>(n),  static_cast<pointer>(0))	;
	}
	void deallocate(void* p, size_type n)
	{
		_deallocate(p);

	}
	void construct(pointer p, const T& value)
	{
		_construct(p, value);
	}
	void destroy(pointer p)
	{
		_destroy(p);
	}
	pointer address(reference x)
	{
		return static_cast<pointer>(&x);
	}

// 	char *_Charalloc(size_type n) {
// 		return  _allocate(static_cast<difference_type>(n),  static_cast<char *>(0))	;
// 	} 

	const_pointer const_address(const_reference x)
	{
		return static_cast<const_pointer>(&x);
	}
	size_type max_size() const
	{
		return size_type(UINT_MAX/sizeof(T));
	}
public:
	MyAllocator(){};
	virtual ~MyAllocator(){};

};

#endif // !defined(AFX_MYALLOCATOR_H__6AFA1B6E_D5A9_4615_A14A_E5A0C9C65D59__INCLUDED_)
