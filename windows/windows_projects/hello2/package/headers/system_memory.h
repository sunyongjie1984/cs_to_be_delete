#pragma once


#include "protocol_interface.h"


enum
{
	_err_allot_memory = _err_memory_start + 1,//分配内存失败
	_err_allot_size,
	_err_array_over,//数组越界错误
};


typedef struct __tag_MEMORY_HANDLE
{
	_STATUS			status_;
	_DATA_TYPE		data_type_;
	_BOOLEAN		delete_data_;
	u_long			allot_size_;
	u_char			* memory_;
}
MEMORY_HANDLE;


extern RESULT __cdecl memory_init		(
											_in_ _out_ MEMORY_HANDLE * h
										);

/*
如果obj状态为_STATUS，
如果allot_size长度等于obj长度，清空obj->mm_data_
否则，销毁obj对象，重新创建obj
否则，创建obj
*/
extern RESULT __cdecl memory_create		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long allot_size
										);

extern RESULT __cdecl memory_recreate	(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long allot_size,
											_in_ const u_long bak_begin_pos,
											_in_ const u_long bak_end_pos
										);
/*
销毁obj
*/
extern RESULT __cdecl memory_destroy	(
											_in_ _out_ MEMORY_HANDLE * h
										);


extern RESULT __cdecl memory_set		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_char ch
										);

/*
返回obj长度
*/
extern RESULT __cdecl memory_size		(
											_in_ const MEMORY_HANDLE * h,
											_out_ u_long * allot_size
										);

/*
将byte_array内容从obj的mm_begin_pos位置写入write_length个字节
*/
extern RESULT __cdecl memory_write		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const u_char * byte_array,
											_in_ const u_long write_length
										);

/*
返回obj的mm_begin_pos位置的指针指向byte_array，并返回read_length字节数
*/
extern RESULT __cdecl memory_read		(
											_in_ const MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_out_ u_char ** byte_array,
											_in_ _out_ u_long * read_length
										);

/*
从in_mm的第in_mm_begin_pos字节开始向后write_length个字节数的内存段，写入obj的以mm_begin_pos字节为起点的内存中
*/
extern RESULT __cdecl memory_write_o	(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const MEMORY_HANDLE * in_mm,
											_in_ const u_long in_mm_begin_pos,
											_in_ const u_long write_length
										);

extern RESULT __cdecl memory_read_o		(
											_in_ const MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ _out_ MEMORY_HANDLE * out_mm,
											_in_ const u_long out_mm_begin_pos,
											_in_ _out_ u_long * read_length
										);

extern RESULT __cdecl memory_copy		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const MEMORY_HANDLE * src
										);

extern RESULT __cdecl memory_compare	(
											_in_ const MEMORY_HANDLE * h,
											_in_ const MEMORY_HANDLE * src,
											_out_ _BOOLEAN * is_same
										);