#pragma once

#include "system_memory.h"
#include "protocol_interface.h"


typedef struct __tag_STRING_HANDLE
{
	_STATUS	status_;
	//struct MEMORY_HANDLE;
}
STRING_HANDLE;


extern RESULT __cdecl string_init	(
											_in_ _out_ STRING_HANDLE * h
										);

/*
如果obj状态为_STATUS，
如果allot_size长度等于obj长度，清空obj->mm_data_
否则，销毁obj对象，重新创建obj
否则，创建obj
*/
extern RESULT __cdecl string_create		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long allot_size
										);

extern RESULT __cdecl string_recreate	(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long allot_size,
											_in_ const u_long bak_begin_pos,
											_in_ const u_long bak_end_pos
										);
/*
销毁obj
*/
extern RESULT __cdecl string_destroy	(
											_in_ _out_ STRING_HANDLE * h
										);


extern RESULT __cdecl string_set		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_char ch
										);

/*
返回obj长度
*/
extern RESULT __cdecl string_length	(
											_in_ const STRING_HANDLE * h,
											_out_ u_long * length
										);

/*
将byte_array内容从obj的mm_begin_pos位置写入write_length个字节
*/
extern RESULT __cdecl string_write		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const u_char * byte_array,
											_in_ const u_long write_length
										);

/*
返回obj的mm_begin_pos位置的指针指向byte_array，并返回read_length字节数
*/
extern RESULT __cdecl string_read		(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_out_ u_char ** byte_array,
											_in_ _out_ u_long * read_length
										);

/*
从in_mm的第in_mm_begin_pos字节开始向后write_length个字节数的内存段，写入obj的以mm_begin_pos字节为起点的内存中
*/
extern RESULT __cdecl string_write_o	(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const STRING_HANDLE * in_mm,
											_in_ const u_long in_mm_begin_pos,
											_in_ const u_long write_length
										);

extern RESULT __cdecl string_read_o		(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ _out_ STRING_HANDLE * out_mm,
											_in_ const u_long out_mm_begin_pos,
											_in_ _out_ u_long * read_length
										);

extern RESULT __cdecl string_compare	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const u_char * src,
											_in_ const u_long src_begin_pos,
											_in_ const u_long cmp_length,
											_out_ _BOOLEAN * is_same
										);

extern RESULT __cdecl string_compare_o	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const STRING_HANDLE * src,
											_in_ const u_long src_begin_pos,
											_in_ const u_long cmp_length,
											_out_ _BOOLEAN * is_same
										);

extern RESULT __cdecl string_upper		(
											_in_ _out_ STRING_HANDLE * h
										);

extern RESULT __cdecl string_lower		(
											_in_ _out_ STRING_HANDLE * h
										);

extern RESULT __cdecl string_first_find	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const u_char * find_str,
											_out_ u_long * find_pos
										);

extern RESULT __cdecl string_last_find	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const u_char * find_str,
											_out_ u_long * find_pos
										);

extern RESULT __cdecl string_copy		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const STRING_HANDLE * src
										);

extern RESULT __cdecl string_append		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_char * append_str,
											_in_ const u_long append_length
										);

extern RESULT __cdecl string_append_o	(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const STRING_HANDLE * append_obj
										);

