CC=g++
CFLAG = -g  -Wno-deprecated
#CFLAG = -o

all  : client server

client :Client.cpp Socket.cpp ../exception/Exception.cpp
	#$(CC) $(CFLAG) Client.cpp Socket.cpp ../exception/Exception.cpp 
	$(CC) $(CFLAG) client Client.cpp Socket.cpp ../exception/Exception.cpp 

server :ServerSide.cpp Socket.cpp ../exception/Exception.cpp  ../thread/ThreadManage.cpp  ../thread/ThreadPool.cpp ../thread/Thread.cpp ../thread/WorkerThread.cpp ../thread/Job.cpp ../sync/sync.cpp -lpthread
	$(CC) $(CFLAG) ServerSide.cpp Socket.cpp ../exception/Exception.cpp  ../thread/ThreadManage.cpp  ../thread/ThreadPool.cpp ../thread/Thread.cpp ../thread/WorkerThread.cpp ../thread/Job.cpp ../sync/sync.cpp -lpthread

clean :
	@rm -f *.o





