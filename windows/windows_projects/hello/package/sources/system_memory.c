#include "../headers/system_memory.h"


#include <memory.h>
#include <stdio.h>



RESULT __cdecl memory_init( _in_ _out_ MEMORY_HANDLE * h )
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}

RESULT __cdecl memory_create( _in_ _out_ MEMORY_HANDLE * h, _in_ const u_long allot_size )
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}


RESULT __cdecl memory_recreate(
								_in_ _out_ MEMORY_HANDLE * h,
								_in_ const u_long allot_size,
								_in_ const u_long bak_begin_pos,
								_in_ const u_long bak_end_pos
								)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}


RESULT __cdecl memory_destroy( _in_ _out_ MEMORY_HANDLE * h )
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}


RESULT __cdecl memory_set( _in_ MEMORY_HANDLE * h, _in_ const u_char ch )
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}


RESULT __cdecl memory_size( _in_ const MEMORY_HANDLE * h, _out_ u_long * allot_size )
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}


RESULT __cdecl memory_write(
							_in_ _out_ MEMORY_HANDLE * h,
							_in_ const u_long mm_begin_pos,
							_in_ const u_char * byte_array,
							_in_ const u_long write_length
							)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}



RESULT __cdecl memory_read(
							_in_ const MEMORY_HANDLE * h,
							_in_ const u_long mm_begin_pos,
							_out_ u_char ** byte_array,
							_in_ _out_ u_long * read_length
							)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}



RESULT __cdecl memory_write_o(
								_in_ _out_ MEMORY_HANDLE * h,
								_in_ const u_long mm_begin_pos,
								_in_ const MEMORY_HANDLE * in_mm,
								_in_ const u_long in_mm_begin_pos,
								_in_ const u_long write_length
								)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}

RESULT __cdecl memory_read_o(
								_in_ const MEMORY_HANDLE * h,
								_in_ const u_long mm_begin_pos,
								_in_ _out_ MEMORY_HANDLE * out_mm,
								_in_ const u_long out_mm_begin_pos,
								_in_ _out_ u_long * read_length
								)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}

RESULT __cdecl memory_copy(
							_in_ _out_ MEMORY_HANDLE * h,
							_in_ const MEMORY_HANDLE * src
							)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}

RESULT __cdecl memory_compare(
								_in_ const MEMORY_HANDLE * h,
								_in_ const MEMORY_HANDLE * src,
								_out_ _BOOLEAN * is_same
								)
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}