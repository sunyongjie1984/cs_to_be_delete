CC=g++
CFLAG = -o

all : server client Sync Job

server : IPCCom.cpp server.cpp
	$(CC) $(CFLAG) server IPCCom.cpp server.cpp

client : IPCCom.cpp client.cpp
	$(CC) $(CFLAG) client IPCCom.cpp client.cpp

Sync    :Sync.cpp
	$(CC) $(CFLAG) Sync Sync.cpp -lpthread

Job    :Job.cpp
	$(CC) $(CFLAG) Job Job.cpp -lpthread


clean :
	@rm -f server
	@rm -f client
	@rm -f *.o





