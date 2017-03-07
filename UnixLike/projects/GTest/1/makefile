##########################################################################
## 模块名称：系统开发框架
## 文件名称：makefile
## 作    者：何李夫
## 开发日期：2013-07-15 10:21:00
## 修改记录:
##
##########################################################################

#(1)变量定义

#输出目标库名
EXES= AddUnitTest

#动态库引出函数定义(不需要)
EXPS=

#源代码路径
NEEQ_HOME = ../../../..

#include路径
INCDIR=-I$(NEEQ_HOME) -I /home/sunyj/software/gtest-1.7.0/include

#dll输出路径
OUTDIR = .

#OBJ扩展名定义
TO=o
LIB_PRE=
LIB_EXT=

#自定义编译(不同平台对同一模块可能有不同编译选项):
DEFS = -DISLIB -DNDEBUG -DVMWARE

#清除文件命令
RM = rm -f


#(2)编译器参数设置
CC = g++
LD = $(CC)

CFLAGS = -c -g -w -fprofile-arcs -ftest-coverage $(DEFS)
#CFLAGS = -c -g -Wall -fprofile-arcs -ftest-coverage $(DEFS)
LFLAGS = -coverage -rdynamic
LIBPATH=$(NEEQ_HOME)/Lib ../gtest-1.7.0/lib/.libs/

#debug版本
ifdef _DEBUG
DEFS= $(DEFS) -D_DEBUG
CFLAGS = -c -g -fPIC $(DEFS)
EXES = $(EXES)_d
endif

#(3)要连接的标准库和自定义库
STDLIBS= -lpthread  -lc -lnsl  -ldl  -lm   -lstdc++ -lrt -lgtest -lgtest_main
DEFLIBS= -L$(NEEQ_HOME)/Lib -L /home/sunyj/software/gtest-1.7.0/lib/.libs

#(4)包含通用编译项
include makefile.inc
