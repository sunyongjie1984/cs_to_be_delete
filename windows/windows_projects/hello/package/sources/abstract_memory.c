

#include "../headers/abstract_memory.h"
#include "object_interface_macro.h"






RESULT __cdecl mm_set( _in_ _out_ MEMORY * obj, _in_ const u_char ch )
{
	RESULT ret;    _INIT_RESULT_(ret)
	return ret;
}


RESULT __cdecl mm_size( _in_ const MEMORY * obj, _out_ u_long * allot_size )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}


RESULT __cdecl mm_write( _in_ _out_ MEMORY * obj, _in_ const u_long mm_begin_pos, _in_ const u_char * byte_array, _in_ const u_long write_length )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}


RESULT __cdecl mm_read( _in_ const MEMORY * obj, _in_ const u_long mm_begin_pos, _out_ u_char ** byte_array, _in_ _out_ u_long * read_length )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}


RESULT __cdecl mm_write_o( _in_ _out_ MEMORY * obj, _in_ const u_long mm_begin_pos, _in_ const MEMORY * in_mm, _in_ const u_long in_mm_begin_pos, _in_ const u_long write_length )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}

RESULT __cdecl mm_read_o( _in_ const MEMORY * obj, _in_ const u_long mm_begin_pos, _in_ _out_ MEMORY * out_mm, _in_ const u_long out_mm_begin_pos, _in_ _out_ u_long * read_length )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}

RESULT __cdecl mm_copy( _in_ _out_ MEMORY * obj, _in_ const MEMORY * src_obj )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}

RESULT __cdecl mm_compare( _in_ const MEMORY * obj, _in_ const MEMORY * src_obj, _out_ _BOOLEAN * is_same )
{
	RESULT ret;    _INIT_RESULT_(ret)
		return ret;
}


_CTOR_( MEMORY )

_SUPER_CTOR_( MEMORY_HANDLE )

_BIND_FUNC_(mm_compare, mm_compare)
_BIND_FUNC_(mm_copy, mm_copy)
_BIND_FUNC_(mm_read_o, mm_read_o)
_BIND_FUNC_(mm_write_o, mm_write_o)
_BIND_FUNC_(mm_read, mm_read)
_BIND_FUNC_(mm_write, mm_write)
_BIND_FUNC_(mm_size, mm_size)
_BIND_FUNC_(mm_set, mm_set)

_END_CTOR_



_DTOR_( MEMORY )
_END_DTOR_

#if 0
#include <memory.h>
#include <stdio.h>



_CTOR_( MEMORY_DATA )
    obj->memory_        = NULL;
    obj->allot_size_    = 0;
_END_CTOR_


_DTOR_( MEMORY_DATA )
    obj->memory_        = NULL;
    obj->allot_size_    = 0;
_END_DTOR_

/*
  如果obj状态为_instance，
        如果allot_size长度等于obj长度，清空obj->mm_data_
        否则，销毁obj对象，重新创建obj
  否则，创建obj
*/
RESULT __cdecl mm_create( MEMORY * obj, const u_long allot_size );
RESULT __cdecl mm_recreate( MEMORY * obj, const u_long allot_size, const u_long bak_begin_pos, const u_long bak_end_pos );
/*
  销毁obj
*/
RESULT __cdecl mm_destroy( MEMORY * obj );


RESULT __cdecl mm_set( MEMORY * obj, const u_char ch )
{
    RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(obj) )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
	    if ( 0 < obj->mm_data_.allot_size_ )
	    {
	        memset(obj->mm_data_.memory_, ch, obj->mm_data_.allot_size_);
	        _SET_RESULT_( ret, _ok, _true )
	    }
	    else
	    {
	        _SET_RESULT_( ret, _err_allot_size, _false )
	        set_debug_depict( &ret );
	    }
	}
	else
	{
        _SET_RESULT_( ret, _err_object_instance, _false )
        set_debug_depict( &ret );
	}
    return ret;
}



RESULT __cdecl mm_size( const MEMORY * obj, u_long * allot_size )
{
    RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(obj) || _IS_NULLITY_POINTER_(allot_size) )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
	    *allot_size = obj->mm_data_.allot_size_;
	    _SET_RESULT_( ret, _ok, _true )
	}
	else
	{
	    *allot_size = 0;
        _SET_RESULT_( ret, _err_object_instance, _false )
        set_debug_depict( &ret );
	}
    return ret;
}



RESULT __cdecl mm_write( MEMORY * obj, const u_long mm_begin_pos, const u_char * byte_array, const u_long write_length )
{
	u_long obj_spare_length = 0;
	u_long obj_length = mm_begin_pos + write_length;

    RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(obj) || _IS_NULLITY_POINTER_(byte_array) || 0x00 > mm_begin_pos || 0x01 > write_length )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
	    obj_spare_length = obj->mm_data_.allot_size_ - mm_begin_pos;

	    if ( write_length > obj_spare_length )
	    {
	        ret = mm_recreate(obj, obj_length, 0, mm_begin_pos);
			if ( _IS_ERR_RESULT_(ret) )
				return ret;
	    }
	}
	else
	{
	    ret = mm_create(obj, obj_length);
	}
	memcpy((obj->mm_data_.memory_) + mm_begin_pos, byte_array, write_length);

	_SET_RESULT_( ret, _ok, _true )

    return ret;
}


RESULT __cdecl mm_read( const MEMORY * obj, const u_long mm_begin_pos, u_char ** byte_array, u_long * read_length )
{
	u_long obj_spare_length = 0;

    RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(obj) || _IS_NULLITY_POINTER_(byte_array) || _IS_NULLITY_POINTER_(read_length) || 0x00 > mm_begin_pos )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( 0x01 > *read_length )
	{
	    _SET_RESULT_( ret, _err_input_para, _false )
	    set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
	    obj_spare_length = obj->mm_data_.allot_size_ - mm_begin_pos;

	    if ( *read_length < obj_spare_length )
	    {
	        *byte_array = obj->mm_data_.memory_ + mm_begin_pos;
	    }
	    else
        {
            *byte_array = NULL;
            *read_length = obj_spare_length;
            _SET_RESULT_( ret, _err_allot_memory, _false )
            set_debug_depict( &ret );
        }
	}
	else
	{
	    *byte_array = NULL;
        *read_length = 0;
	    _SET_RESULT_( ret, _err_object_instance, _false )
	    set_debug_depict( &ret );
	}
    return ret;
}

RESULT __cdecl mm_write_o( MEMORY * obj, const u_long mm_begin_pos, const MEMORY * in_mm, const u_long in_mm_begin_pos, const u_long write_length )
{
    RESULT ret;    _INIT_RESULT_(ret)
    return ret;
}

RESULT __cdecl mm_read_o( const MEMORY * obj, const u_long mm_begin_pos, MEMORY * out_mm, const u_long out_mm_begin_pos,  u_long * read_length )
{
    RESULT ret;    _INIT_RESULT_(ret)
    return ret;
}

RESULT __cdecl mm_copy( _in_ MEMORY * obj, _in_ const MEMORY * src_obj )
{
	u_long copy_length = 0;
	u_char * bype_array = NULL;
	
	RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(src_obj) )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_NO_INSTANCE_(src_obj->instance_) )
	{
	    _SET_RESULT_( ret, _err_input_para, _false )
	    set_debug_depict( &ret );
		return ret;
	}
	ret = src_obj->mm_size(src_obj, &copy_length);

	if ( _IS_OK_RESULT_(ret) )
	{
	    ret = mm_create(obj, copy_length);

	    if ( _IS_OK_RESULT_(ret) )
	    {
	        ret = src_obj->mm_read(src_obj, 0, &bype_array, &copy_length);

	        if ( _IS_OK_RESULT_(ret) )
	            ret = obj->mm_write(obj, 0, bype_array, copy_length);
	    }
	}
    return ret;
}

RESULT __cdecl mm_compare( _in_ const MEMORY * obj, _in_ const MEMORY * src_obj, _BOOLEAN * is_same )
{
	u_long obj_length		= 0;
	u_long src_obj_length	= 0;

	u_char * obj_array		= NULL;
	u_char * src_obj_array	= NULL;

	RESULT ret;    _INIT_RESULT_(ret)

	if ( _IS_NULLITY_POINTER_(src_obj) || _IS_NULLITY_POINTER_(is_same) )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_NO_INSTANCE_(src_obj->instance_) )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	ret = src_obj->mm_size(src_obj, &src_obj_length);

	if ( _IS_ERR_RESULT_(ret) )
		return ret;

	ret = obj->mm_size(obj, &obj_length);

	if ( _IS_ERR_RESULT_(ret) )
		return ret;

	*is_same = _false;

	if ( obj_length == src_obj_length )
	{
		ret = src_obj->mm_read(src_obj, 0, &src_obj_array, &src_obj_length);

		if ( _IS_ERR_RESULT_(ret) )
			return ret;

		ret = obj->mm_read(obj, 0, &obj_array, &obj_length);

		if ( _IS_ERR_RESULT_(ret) )
			return ret;

		if ( 0 != memcmp(obj_array, src_obj_array, obj_length) )
			*is_same = _true;

		_SET_RESULT_( ret, _ok, _true )
	}
	return ret;
}


_CTOR_( MEMORY )

    CTOR_MEMORY_DATA(&(obj->mm_data_));

    _BIND_FUNC_(mm_compare, mm_compare)
    _BIND_FUNC_(mm_copy, mm_copy)
    _BIND_FUNC_(mm_read_o, mm_read_o)
    _BIND_FUNC_(mm_write_o, mm_write_o)
    _BIND_FUNC_(mm_read, mm_read)
    _BIND_FUNC_(mm_write, mm_write)
    _BIND_FUNC_(mm_size, mm_size)
    _BIND_FUNC_(mm_set, mm_set)

_END_CTOR_



_DTOR_( MEMORY )
    mm_destroy(obj);
_END_DTOR_



/*
*/

RESULT __cdecl mm_create( MEMORY * obj, const u_long allot_size )
{
    RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(obj) || 0x00000001 > allot_size )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
    if ( _IS_NO_INSTANCE_( obj->instance_ ) )
	{
		_SET_RESULT_( ret, _err_object_instance, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
	    if ( allot_size != obj->mm_data_.allot_size_ )
	    {
	        ret = mm_destroy(obj);
	        if ( _IS_ERR_RESULT_( ret ) )
                return ret;
	    }
	}
	if ( _IS_NO_INSTANCE_(obj->mm_data_.instance_) )
	{
	    CTOR_MEMORY_DATA( &(obj->mm_data_) );
	    obj->mm_data_.memory_ = (u_char *)malloc(allot_size);
	}
	if ( _IS_OK_POINTER_(obj->mm_data_.memory_) )
	{
	    obj->mm_data_.allot_size_ = allot_size;
	    ret = obj->mm_set(obj, '0');
	}
	else
	{
	    _SET_RESULT_( ret, _err_allot_memory, _false )
	    set_debug_depict( &ret );
	}
    return ret;
}

/*

*/
RESULT __cdecl mm_recreate( MEMORY * obj, const u_long allot_size, const u_long bak_begin_pos, const u_long bak_end_pos )
{
	u_char * buff = NULL;
	u_long length = 0;
	RESULT ret;    _INIT_RESULT_(ret)

	if ( _IS_NULLITY_POINTER_(obj))
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_NO_INSTANCE_( obj->instance_ ) )
	{
		_SET_RESULT_( ret, _err_object_instance, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
		ret = obj->mm_size(obj, &length);

		if ( _IS_OK_RESULT_(ret) )
		{
			if ( allot_size < length )
			{
				return ret;
			}
			buff = (u_char *)malloc(bak_end_pos - bak_begin_pos);

			if ( _IS_OK_POINTER_(buff) )
			{
				memcpy( buff, (obj->mm_data_.memory_) + bak_begin_pos, bak_end_pos - bak_begin_pos );
			}
		}
	}
	ret = mm_create(obj, allot_size);

	if ( _IS_OK_RESULT_(ret) )
	{
		if ( bak_begin_pos >= 0 && bak_end_pos >= 0 && bak_begin_pos != bak_end_pos )
			memcpy( (obj->mm_data_.memory_) + bak_begin_pos, buff, bak_end_pos - bak_begin_pos );
	}
	if ( buff )
	{
		free(buff);
		buff = NULL;
	}
	return ret;
}

RESULT __cdecl mm_destroy( MEMORY * obj )
{
    RESULT ret;    _INIT_RESULT_(ret)

    if ( _IS_NULLITY_POINTER_(obj) )
	{
		_SET_RESULT_( ret, _err_input_para, _false )
		set_debug_depict( &ret );
		return ret;
	}
	if ( _IS_INSTANCE_(obj->mm_data_.instance_) )
	{
	    if ( _IS_OK_POINTER_(obj->mm_data_.memory_) )
	    {
	        free( obj->mm_data_.memory_ );
	        DTOR_MEMORY_DATA( &(obj->mm_data_) );

	        _SET_RESULT_( ret, _ok, _true )
	    }
        else
	    {
	        _SET_RESULT_( ret, _err_allot_size, _false )
	    }
	}
	else
	{
	    _SET_RESULT_( ret, _failed, _false )
	    set_debug_depict( &ret );
	}
    return ret;
}
#endif//0