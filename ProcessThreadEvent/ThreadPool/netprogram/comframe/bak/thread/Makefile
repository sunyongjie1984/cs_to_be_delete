CC=g++
CFLAG = -g  -Wno-deprecated

all : pooltest 

#manage : ThreadManage.cpp Thread.cpp ThreadPool.cpp  WorkerThread.cpp Job.cpp ../sync/sync.cpp
#	$(CC) $(CFLAG) manage ThreadManage.cpp Thread.cpp ThreadPool.cpp Job.cpp WorkerThread.cpp ../sync/sync.cpp -lpthread

pooltest :PoolTest.cpp ThreadManage.cpp Thread.cpp ThreadPool.cpp  WorkerThread.cpp Job.cpp ../sync/sync.cpp
	$(CC) $(CFLAG) PoolTest.cpp ThreadManage.cpp Thread.cpp ThreadPool.cpp Job.cpp WorkerThread.cpp ../sync/sync.cpp -lpthread
clean :
	@rm -f *.o





