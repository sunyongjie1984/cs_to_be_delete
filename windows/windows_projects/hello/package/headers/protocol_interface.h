#pragma once

#include "protocol_enum.h"
#include "protocol_macro.h"
#include "protocol_type_define.h"


/******************************************************************************************/
//定义函数
//函数命名 --> 单词小写，“_”分隔
//函数参数 --> 使用_in_ / _out_表示参数走向
//函数返回 --> 使用RESULT类型表示返回状态
/******************************************************************************************/

// 测试函数
extern RESULT __cdecl test_func_name( _in_ const u_char t, _in_ _out_ u_char * buff );

extern int __cdecl get_error( void );
extern void __cdecl set_debug_depict(_in_ _out_ RESULT * ret);
