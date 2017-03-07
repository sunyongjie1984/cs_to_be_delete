CC=g++
CFLAG = -g  -Wno-deprecated
#CFLAG = -o  -Wno-deprecated
#CFLAG = -o

THREAD = ${HOME}/netprogram/comframe/thread
SOCKET = ${HOME}/netprogram/comframe/socket
SYNC   = ${HOME}/netprogram/comframe/sync
EXCEPTION = ${HOME}/netprogram/comframe/exception

all  : HTTPServer

HTTPServer :${SOCKET}/ServerSide.cpp ${SOCKET}/Socket.cpp ${EXCEPTION}/Exception.cpp  ${THREAD}/ThreadManage.cpp  ${THREAD}/ThreadPool.cpp ${THREAD}/Thread.cpp ${THREAD}/WorkerThread.cpp ${THREAD}/Job.cpp ${SYNC}/sync.cpp HTTPServer.cpp -lpthread
	$(CC) $(CFLAG) ${SOCKET}/ServerSide.cpp ${SOCKET}/Socket.cpp ${EXCEPTION}/Exception.cpp  ${THREAD}/ThreadManage.cpp  ${THREAD}/ThreadPool.cpp ${THREAD}/Thread.cpp ${THREAD}/WorkerThread.cpp ${THREAD}/Job.cpp ${SYNC}/sync.cpp HTTPServer.cpp -lpthread

clean :
	@rm -f *.o





