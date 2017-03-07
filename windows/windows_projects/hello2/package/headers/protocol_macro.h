#pragma once


/******************************************************************************************/
//定义宏变量
//命名规则 -> "_" + 单词大写,“_”分隔，以“_”最为结束符
/******************************************************************************************/

// 判断指针是否为空
#define _IS_NULLITY_POINTER_( pointer )			NULL == (pointer)

// 判断指针是否非空
#define _IS_OK_POINTER_( pointer )			    NULL != (pointer)

// 开启set_debug_depict()函数的宏
#define _DEBUG_DEPICT_

// 设置结果对象的状态和错误号
#define _SET_RESULT_( ret, err, results )	    {										\
                                                    (ret).error_ = (err);		    	\
                                                    (ret).result_ = (results);		    \
													set_debug_depict( &(ret) );			\
                                                }

#define _RETURN_RESULT_( ret, err, results )	    {										\
													(ret).error_ = (err);		    	\
													(ret).result_ = (results);		    \
													set_debug_depict( &(ret) );			\
													return (ret);						\
												}

#if 0
// 复制结果对象
#define _COPY_RESULT_( dest_ret, src_ret )		_SET_RESULT_( dest_ret,				    \
                                                              (src_ret).error_,			\
                                                              (src_ret).result_ )
#endif//0

// 初始化结果对象
#define _INIT_RESULT_( ret )    				_SET_RESULT_( ret, -1, _false )

// 是否成功
#define _IS_OK_( results )						_true == (results)

// 是否失败
#define _IS_ERR_( results )					    _false == (results)

// 是否已经实例化
#define _IS_INSTANCE_( status )					_instance == (status)

// 是否已经实例化
#define _IS_CREATE_( status )					_create == (status)

// 是否已经实例化
#define _IS_NO_STATUS_( status )				_instance != (status)

// 判断结果的状态是否为成功
#define _IS_OK_RESULT_( ret )				    _IS_OK_( (ret).result_ )

#define _IS_ERR_RESULT_( ret )				    _IS_ERR_( (ret).result_ )





/******************************************************************************************/
//空的宏命名规则 -> "_" + 单词小写,“_”分隔，以“_”最为结束符
/******************************************************************************************/

//函数参数的走向
#define _in_
#define _out_

#define _windows_sys_




/******************************************************************************************/
// 类的宏定义和new、delete、构造和析构函数的声明
/******************************************************************************************/

#define _CLASS_(class_name)								\
typedef struct class_name class_name;					\
class_name * NEW_##class_name();						\
void DELETE_##class_name(class_name * obj);				\
void CTOR_##class_name(class_name * obj);				\
void DTOR_##class_name(class_name * obj);				\
struct class_name



#define EXTENDS(type)		struct type type

