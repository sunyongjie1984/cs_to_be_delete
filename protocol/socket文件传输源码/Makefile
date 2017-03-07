DLL=libunmsocket.so

CC=g++
CPPFLAGS=
BINDIR=bin
CFLAGS=-Wall -O2 -g
CXXFLAGS=$(CFLAGS)
COMPILE=$(CC) $(CPPFLAGS) $(CFLAGS) -c 
INCLUDE=-I/usr/include/glib-1.2/ -I/usr/lib/glib/include -I../../common 

SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SRCS))
LIB = ../../common/libnas.a
all: $(DLL)

$(DLL): $(OBJS)
	$(CC) -o $(DLL) $(OBJS) $(LIB) -shared
	if [ ! -d $(BINDIR) ];then \
		mkdir $(BINDIR);\
	fi
	cp -f $(DLL) $(BINDIR) 
	cp -f $(DLL) /usr/naslib
%.o: %.cpp
	$(COMPILE) $(INCLUDE) -o $@ $<

clean:
	-rm $(OBJS) $(DLL) $(DEPS)

explain:
	@echo "Final cgi file name: $(DLL)"
	@echo "Source files: $(SRCS)" 
	@echo "Object files: $(OBJS)"
	@echo "Dependency files: $(DEPS)"


