#pragma once

#include "protocol_interface.h"
#include "system_memory.h"


typedef struct __tag_LINKED_NODE
{
	_STATUS	status_;
	MEMORY_HANDLE data_;

	struct __tag_LINKED_NODE * previous_;
	struct __tag_LINKED_NODE * next_;
}
LINKED_NODE;

typedef struct __tag_LINKED_HANDLE 
{
	_STATUS	status_;
	u_long		linked_length_;

	LINKED_NODE	* head_;
	LINKED_NODE	* tail_;
}
LINKED_HANDLE;



extern RESULT __cdecl linked_init		(
											_in_ _out_ LINKED_HANDLE * h
										);

extern RESULT __cdecl linked_insert		(
											_in_ _out_ LINKED_HANDLE * h,
											_in_ const int index
										);

extern RESULT __cdecl linked_get		(
											_in_ const LINKED_HANDLE * h,
											_out_ MEMORY_HANDLE ** node_obj,
											_in_ const int index
										);

extern RESULT __cdecl linked_erase		(
											_in_ _out_ LINKED_HANDLE * h,
											_in_ const int index
										);

extern RESULT __cdecl linked_length		(
											_in_ const LINKED_HANDLE * h,
											_out_ int * length
										);

extern RESULT __cdecl linked_first_find	(
											_in_ const LINKED_HANDLE * h,
											_in_ const MEMORY_HANDLE * find_obj,
											_out_ int * index
										);

extern RESULT __cdecl linked_last_find	(
											_in_ const LINKED_HANDLE * h,
											_in_ const MEMORY_HANDLE * find_obj,
											_out_ int * index
										);

extern RESULT __cdecl linked_pop_front	(
											_in_ _out_ LINKED_HANDLE * h,
											_out_ MEMORY_HANDLE ** pop_obj
										);

extern RESULT __cdecl linked_pop_back	(
											_in_ _out_ LINKED_HANDLE * h,
											_out_ MEMORY_HANDLE ** pop_obj
										);

extern RESULT __cdecl linked_push_back	(
											_in_ _out_ LINKED_HANDLE * h,
											_in_ const MEMORY_HANDLE * last_obj
										);



typedef struct __tag_BINTREE_NODE
{
	_STATUS	status_;
	MEMORY_HANDLE data_;

	struct __tag_BINTREE_NODE * father_;
	struct __tag_BINTREE_NODE * left_chield_;
	struct __tag_BINTREE_NODE * right_chield_;
}
BINTREE_NODE;

typedef struct __tag_BINTREE_HANDLE 
{
	_STATUS		status_;

	BINTREE_NODE	* root_;
}
BINTREE_HANDLE;