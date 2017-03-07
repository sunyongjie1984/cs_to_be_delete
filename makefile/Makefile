#############################################################################
# Makefile for building: sample 2011-09-26
#
# Project: 
# Template:
# Command:
#							------基本上简单用法的makefile-------
#1. 第一个目标为最终目标
#2. 命令以 Tab开头，可以有多个命令
#3. 分行号\ 后面不可以跟空格
#4、加@可以去掉命令显示
#5. 变量为 abc = efd     访问为 $(abc)  echo $abc
#
#
#
#缺点，单文件夹
#每次都会重新生成
#
#foo.o : foo.c defs.h # foo模块
#cc -c -g foo.c
#
#多目录  一种方法，在主目录里面include ""，然后其里面OBJS +=  .o，这样其实就是   或用foreach
#############################################################################
#target
EXECUTABLE := test

CC          := gcc
CXX         := g++
STRIP       := strip
AR          := ar cqs
LINK        := g++
RM			:= rm -f


CFLAGS      := -g -Wall
CXXFLAGS    := $(CFLAGS)
CXXFLAGS	+= -MD


LIBS        := -lm 
LIBPATH		:= -L/usr/local/lib
INCPATH     := 

####### Output directory
OBJSPATH	:= ../Obj/
EXECUTABLEPATH := ../Execute/

#######source Files
SOURCE	:= $(wildcard *.c) $(wildcard *.cpp)
OBJS	:= $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCE)))
DEPS	:= $(patsubst %.o,%.d,$(OBJS))

#######rule
.SUFFIXES: .cpp .c .o .so .a .d
$(OBJSPATH)%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJSPATH)%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(OBJSPATH)%.d:%.cpp
	$(CXX) -MM $< > $@


######main
.PHONY : all deps objs clean rebuild
all: $(EXECUTABLE)
	$(CXX) $(CXXFLAGS) $(INCLUDEPATH) $(LIBS) $(LIBPATH) $(addprefix $(OBJSPATH),$(OBJS)) \
	-o $(EXECUTABLEPATH)$(EXECUTABLE)

deps: $(addprefix $(OBJSPATH),$(DEPS))
objs: $(addprefix $(OBJSPATH),$(OBJS))

clean:
	@$(RM) $(OBJSPATH)*.o
	@$(RM) $(OBJSPATH)*.d
	@$(RM) $(EXECUTABLEPATH)$(EXECUTABLE)
rebuild: clean all	
-include $(addprefix $(OBJSPATH),$(DEPS)) ##.d里面是详细的.o rule   自己会括展开的，然后没有文件就自己去重建
$(EXECUTABLE) : objs



