代码约定

	目录结构：
		headers
		sources
		binary
		library
		solution
		project
		document

	文件命名：
		public_define_
		project_define_ + system_windows_ / system_linux_
		abstract_
		frame_
		logic_

	枚举声明:
		“_”分隔 + 单词小写

	类型声明：
		定义结构 --> 单词大写，“_”分隔 + OBJECT
		定义BOOLEAN类型 _true, _false
		定义RESULT

	常量声明:
		"_" + 单词小写,“_”分隔

	宏声明：
		命名规则 --> "_" + 单词大写,“_”分隔

	变量声明：
		临时变量命名 --> 单词小写 + “_”分隔

		成员变量命名 --> 单词小写 + “_”分隔 + “_”结尾

	函数声明：
		C语言
			函数命名 --> 单词小写，“_”分隔
			函数参数 --> 使用_IN / _OUT表示参数走向
			函数返回 --> 使用RESULT类型表示返回状态




thread
event
thread_lock
file_io
folder
queue
list
array
udp
tcp
memory
string
print
tree

