#======================================================================production project
start : threadbase.o task.o worker.o pool.o manager.o socket.o testpooltask.o serverstart.o 
	g++ threadbase.o task.o worker.o threadpool.o threadmanager.o socket.o testpooltask.o serverstart.o -lpthread -o serverstart
	  
#======================================================================solo compile
threadbase.o : ../../threadmanage/baseclass/threadbase.cpp ../../threadmanage/baseclass/threadbase.h ../../include/publicpact.h
	       g++ -c ../../threadmanage/baseclass/threadbase.cpp

#----------------------------------------------------------------------
task.o : ../../threadmanage/threadpool/task.cpp ../../threadmanage/threadpool/task.h 
	 g++ -c ../../threadmanage/threadpool/task.cpp

#----------------------------------------------------------------------
worker.o : ../../threadmanage/threadpool/worker.cpp ../../threadmanage/threadpool/worker.h
	   g++ -c ../../threadmanage/threadpool/worker.cpp

#----------------------------------------------------------------------
pool.o : ../../threadmanage/threadpool/threadpool.cpp ../../threadmanage/threadpool/threadpool.h
	 g++ -c ../../threadmanage/threadpool/threadpool.cpp

#----------------------------------------------------------------------
manager.o : ../../threadmanage/threadpool/threadmanager.cpp ../../threadmanage/threadpool/threadmanager.h
	    g++ -c ../../threadmanage/threadpool/threadmanager.cpp
	    
#======================================================================solo compile
socket.o : ../../network/socket/socket.cpp ../../network/socket/socket.h ../../include/publicpact.h
	       g++ -c ../../network/socket/socket.cpp

#----------------------------------------------------------------------
testpooltask.o : ../../source/server/testpooltask.cpp ../../source/server/testpooltask.h ../../network/formula/callpact.h
	       g++ -c ../../source/server/testpooltask.cpp

#----------------------------------------------------------------------
serverstart.o : ../../source/server/serverstart.cpp ../../network/socket/socket.h
	  g++ -c ../../source/server/serverstart.cpp

#======================================================================clean objfile and exefile
clean_all:
	rm *.o
	rm serverstart

#----------------------------------------------------------------------clean exefile
clean_out:
	rm serverstart

#----------------------------------------------------------------------clean objfile
clean_obj:
	rm *.o
