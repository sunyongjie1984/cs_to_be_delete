CC=g++
CFLAG = -g  -Wno-deprecated
#CFLAG = -o

all : server 

server :Server.cpp Socket.cpp ../exception/Exception.cpp
	$(CC) $(CFLAG) Server.cpp Socket.cpp ../exception/Exception.cpp 
clean :
	@rm -f *.o





