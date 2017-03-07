#pragma once



/******************************************************************************************/
//定义公共枚举
//枚举值的命名规则 ->“_”为开头， + 单词小写 + 分隔“_”
//枚举类型定义规则 ->“_”为开头， + 单词大写 + 分隔“_”
/******************************************************************************************/

// 函数执行时状态是否正确
typedef enum
{
	_false	= 0x00000000,
	_true	= 0x00000001
}
_BOOLEAN;

// 函数执行时的错误号
typedef enum
{
	_ok		= 0x00000000,
	_failed	= 0x00000001,
	_err_unknown,//未知错误
	_err_input_para,//输入函数的参数错误
	_err_object_instance,//没有实例化
	_err_object_create,//没有实例化
	_err_object_destroy,//销毁错误
	_err_memory_start = 0x01000001,
	_err_socket_start = 0x01100001,
	_err_thread_start
}
_ERROR;

// 数据类型
typedef enum
{
	_data_type	= 0x00100000
}
_DATA_TYPE;


typedef enum
{
	_instance = 0x00001000,
	_create,
	_destroy,
	_callback,
	_thread_status_start
}
_STATUS;

// 数组长度的枚举值
enum _ARRAY_LEN
{
	_L_256 = 256,
};

