// DefaultAllocator.h: interface for the DefaultAllocator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_DEFAULTALLOCATOR_H__B8F4993D_12E7_4046_BDB1_6FF5E01A0783__INCLUDED_
#define AFX_DEFAULTALLOCATOR_H__B8F4993D_12E7_4046_BDB1_6FF5E01A0783__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyAllocator.h"
const int __ALIGN = 8;
const int 	__MAX_BYTES = 128;
const int _NFREELISTS = __MAX_BYTES / __ALIGN;
union obj{
	union obj* free_list_link;
	char client_data[1];
	};
template<class T>
T* _DefaultAllocate( size_t n, const T* hint = 0)
{
	obj* volatile * my_free_list;
	obj* result;
	if ( n * sizeof(T) > (size_t) __MAX_BYTES)
	{
		return MyAllocator<T>::allocate(n, hint);
	}
	my_free_list = DefaultAllocator<T>::free_list + DefaultAllocator<T>::FREELIST_INDEX(n * sizeof(T));
	result = *my_free_list;
	if ( result == 0)
	{
		void* r = DefaultAllocator<T>::refill(DefaultAllocator<T>::ROUND_UP(n * sizeof(T)));
		return (T*)r;
	}
	*my_free_list = result->free_list_link;
	return (T*)result;
}

template<class T>
class DefaultAllocator  
{
public:
	typedef T    value_type;
	typedef T*   pointer;
	typedef const T* const_pointer;
	typedef T&     reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	static obj* volatile free_list[_NFREELISTS];
private:
	static char* start_free;
	static char* end_free;
	static size_t heap_size;
	
public:
	static size_t ROUND_UP(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1) );
	}


public:
	
	static char* chunk_alloc(size_t size, int &nobjs)
	{
		char* result;
		size_type total_bytes = size * nobjs;
		size_type bytes_left = end_free - start_free;
		if ( bytes_left >= total_bytes )
		{
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else if ( bytes_left >= size )
		{
			nobjs = bytes_left / size;
			total_bytes = size * nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else {
			size_type bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if ( bytes_left > 0 )
			{
				obj* volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			start_free = (char*)malloc(bytes_to_get);
			if ( 0 == start_free )
			{
				int i;
				obj* volatile * my_free_list, *p;
				for( i = size; i <= __MAX_BYTES; i+=__ALIGN)
				{
					my_free_list = free_list + FREELIST_INDEX(i * sizeof(T));
					p = * my_free_list;
					if (NULL != p)
					{
						*my_free_list = p->free_list_link;
						start_free = (char*)(p);
						end_free = start_free + i;
						return chunk_alloc(size, nobjs);
					}
				}
				end_free = 0;
				start_free = (char*)MyAllocator<T>::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(size, nobjs);
		}
	}
		
	static size_t FREELIST_INDEX(size_t bytes){
		return ((bytes + __ALIGN - 1)/__ALIGN - 1);
	}
	static void* refill(size_t n)
	{
		int nobjs = 20;
		char* chunk = chunk_alloc(n, nobjs);
		obj* volatile * my_free_list;obj* result;
		obj* current_obj, * next_obj;
		int i;
		if( 1 == nobjs )
		{
			return chunk;
		}
		my_free_list = free_list + FREELIST_INDEX(n * sizeof(T));
		result = (obj*)chunk;
		*my_free_list = next_obj = (obj*)(chunk + n);
		for(i = 1;; i++)
		{
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if(nobjs - 1 == i)
			{
				current_obj->free_list_link = 0;
				break;
			}
			else
			{
				current_obj->free_list_link = next_obj;
			}
		}
		return result;
	}

	char *_Charalloc(size_type n) {
		return  _DefaultAllocate(static_cast<difference_type>(n),  static_cast<char *>(0))	;
	} 
	void construct(pointer p, const T& value)
	{
		_construct(p, value);
	}
	void destroy(pointer p)
	{
		_destroy(p);
	}
	pointer allocate( size_type n, const void* hint = 0)
	{
		return _DefaultAllocate(static_cast<difference_type>(n),  static_cast<pointer>(0));
	}
	static void deallocate(void* p,size_t n)
	{
		if (NULL != p && 0 != n )
		{
			obj* q = (obj*)p;
			obj* volatile * my_free_list;
			if (n * sizeof(T) > (size_type) __MAX_BYTES)
			{
				MyAllocator<T>::deallocate(p, n);
				return;
			}
			my_free_list = free_list + FREELIST_INDEX(n* sizeof(T));
			q->free_list_link = *my_free_list;
			*my_free_list = q;
		}
		
	}
public:
	DefaultAllocator(){};
	virtual	~DefaultAllocator()
	{
		for(int i = 0; i < _NFREELISTS; i++)
		{
			free(free_list[i]);
			free_list[i] = NULL;
		}
	}
	
};
template<class T>
char* DefaultAllocator<T>::start_free = 0;
template<class T>
char*  DefaultAllocator<T>::end_free = 0;
template<class T>
size_t DefaultAllocator<T>::heap_size = 0;
template<class T>
obj * volatile 
DefaultAllocator<T>::free_list[_NFREELISTS] = 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};



#endif // !defined(AFX_DEFAULTALLOCATOR_H__B8F4993D_12E7_4046_BDB1_6FF5E01A0783__INCLUDED_)
