# ----------------------------------------------------------------------------------------------------------------------------------------
# 程序运行方法 ：python odbchelper.py
# 输出结果 :     server=mpilgrim;uid=sa;database=master;pwd=secret
#
# 函数声明方法 ：以关键字 def 开始, 接着为函数名, 再往后为参数, 参数放在小括号里； 多个参数之间用逗号分隔。
#               例如：def buildConnectionString(params):
#
# 函数参数定义 ：Python 中参数params 不需要指定数据类型。 Python 会判定一个变量是什么类型, 并在内部将其记录下来。
#
# 函数返回值 ：  Python 不需要指定返回值的数据类型；不需要指定是否有返回值。
#               实际上, 每个 Python 函数都返回一个值；如果函数执行过 return 语句,
#               它将返回指定的值, 否则将返回 None ( Python 的空值) 。
#
# 对象 ：       一切都可以赋值给变量或作为参数传递给函数。
#               在 Python 中, 函数同其它东西一样也是对象。Python 函数有属性, 并且这些属性在运行时是可用的。在 Python 中
#               一切都是对象, 并且几乎一切都有属性和方法。 所有的函数都有一个内置的 __doc__ 属性, 它会返回在函数源代码中
#               定义的 doc string 。 sys 模块是一个对象, 它有一个叫作 path 的属性。
#
# 代码块 ：     是指函数、if 语句、for 循环、while 循环等等。
#
# 代码缩进 ：   Python 函数没有明显的 begin 和 end, 没有花括号, 用于标识函数的开始和结束。 唯一的分隔符是一个冒号 (:)。
#              代码块通过它们的缩进来定义的，开始缩进表示块的开始, 取消缩进表示块的结束。
#              这个函数代码 (包括 doc string) 缩进了 4 个空格。不一定非要是 4, 只要一致就可以了。没有缩进的第一行则在函数体之外。
#
# 程序注释 ：
#              井（#）字符表示从这个符号出现一直到该语句行结尾的文字将是一个程序注释。
# ----------------------------------------------------------------------------------------------------------------------------------------


def buildConnectionString(params):
    """Build a connection string from a dictionary of parameters.

    Returns string."""
    return ";".join(["%s=%s" % (k, v) for k, v in params.items()])


# ---------------------------------------------------------------------------------------------------------------------------------------- 
# 三重引号 ：   是一种定义既包含单引号又包含双引号的字符串的简单方法。三重引号表示一个多行字符串, 
#              在开始与结束引号间的所有东西都被视为单个字符串的一部分, 包括硬回车和其它的引号字符。
#
# doc string ：在三重引号中的任何东西都是这个函数的 doc string，doc string 在运行时可作为函数的属性。
#              doc string必须是一个函数要定义的第一个内容( 也就是说, 在冒号后面的第一个内容 )。
#
# 文档化函数 ： 许多 Python IDE 使用 doc string 来提供上下文敏感文档信息, 所以当键入一个函数名时, 
#              它的 doc string 显示为一个工具提示。这一点可以说非常有用, 但是它的好坏取决于您书写
#              的 doc string 的好坏。
#
# 使用 if __name__ 的技巧 : 
#              if 表达式无需使用圆括号括起来。 其次, if 语句以冒号结束, 随后跟随的是 缩进代码。
#
# 模块内置属性 __name__ : 
#              所有的模块都有一个内置属性 __name__。一个模块的 __name__ 的值要看您如何应用模块。
#              如果 import 模块, 那么 __name__ 的值通常为模块的文件名, 不带路径或者文件扩展名。
#              但是您也可以像一个标准的程序一样直接运行模块, 在这种情况下 __name__ 的值将是一个特别的缺省值, __main__。
#
# Python 使用 == 做比较, 使用 = 做赋值。 Python 不支持行内赋值, 所以不会出现想要进行比较却意外地出现赋值的情况。
# ----------------------------------------------------------------------------------------------------------------------------------------


if __name__ == "__main__":
    myParams = {"server":"mpilgrim", \
                "database":"master", \
                "uid":"sa", \
                "pwd":"secret" \
                }
    print buildConnectionString(myParams)


# ----------------------------------------------------------------------------------------------------------------------------------------
# 操作 Python IDE （Python 的辅助开发）：
#               访问函数的 doc string - 在命令行中启动 Python.exe,然后在 Python 提示信息下输入命令
#               >>> import odbchelper
#               >>> params = {"server":"mpilgrim", "database":"master", "uid":"sa", "pwd":"secret"}
#               >>> print odbchelper.buildConnectionString(params)
#               server=mpilgrim;uid=sa;database=master;pwd=secret
#               >>> print odbchelper.buildConnectionString.__doc__
#               Build a connection string from a dictionary
#
#               Returns string.
#               >>> import sys
#               >>> sys.path                   
#               ['', '/usr/local/lib/python2.2', '/usr/local/lib/python2.2/plat-linux2',
#               '/usr/local/lib/python2.2/lib-dynload', '/usr/local/lib/python2.2/site-packages',
#               '/usr/local/lib/python2.2/site-packages/PIL', '/usr/local/lib/python2.2/site-packages/piddle']
#               >>> sys                        
#               <module 'sys' (built-in)>
#               >>> sys.path.append('/my/new/path')
#               >>> import odbchelper
#               >>> odbchelper.__name__
#               'odbchelper'
#
# 模块 ：       是指可以交互使用的一个代码段, 或者来自一个大规模的 Python 程序。一旦导入了一个模块,
#               就可以引用它的任何公共的函数、类或属性。模块可以通过这种方法来使用其它模块的功能。
#
# Python IDE操作的解释 ：
#               [import odbchelper] 将 odbchelper 程序作为模块导入。import 一个 Python 模块, 可以使用 module.function 来访问它的函数；
#               [print odbchelper.buildConnectionString(params)] 使用在被导入模块中定义的函数时, 必须包含模块的名字。
#               [print odbchelper.buildConnectionString.__doc__] 访问函数的 __doc__ 属性。
#               [import sys] 导入 sys 模块, 使得它的所有函数和属性都有效。模块导入的搜索路径，当导入一个模块时, Python 在几个地方进行搜索。 
#                            它会按所有定义在 sys.path 中的目录进行搜索。它只是一个list (列表), 可以查看它或通过标准的list方法来修改它。
#               [sys.path] 是一个组成当前搜索路径的目录列表。
# ----------------------------------------------------------------------------------------------------------------------------------------

