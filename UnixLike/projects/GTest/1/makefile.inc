##########################################################################
## 模块名称：系统开发框架
## 文件名称：makefile
## 作    者：何李夫
## 开发日期：2013-07-15 10:21:00
## 修改记录:
##
##########################################################################
#目标文件表
OBJS = add.$(TO)\
       AddUnitTest.$(TO)\

all: cleanobj $(EXES)

add.$(TO):add.cpp
	$(CC) $(CFLAGS) add.cpp $(INCDIR)
 AddUnitTest.$(TO): AddUnitTest.cpp
	$(CC) $(CFLAGS) AddUnitTest.cpp $(INCDIR)

$(EXES): $(OBJS)
	$(LD) $(LFLAGS) -o$(OUTDIR)/$(EXES) $(OBJS) $(STDLIBS) $(DEFLIBS) $(EXPS)

#(3)清理命令
cleanobj:
	$(RM) -rf *.$(TO) *.gcda *.gcno AddUnitTest cov_report* core*
clean:cleanobj
	@echo clean all
