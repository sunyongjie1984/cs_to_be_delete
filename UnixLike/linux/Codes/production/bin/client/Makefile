#======================================================================production project
start : socket.o clientstart.o 
	g++ socket.o clientstart.o -o clientstart

#======================================================================solo compile
socket.o : ../../network/socket/socket.cpp ../../network/socket/socket.h ../../include/publicpact.h
	       g++ -c ../../network/socket/socket.cpp

#----------------------------------------------------------------------
clientstart.o : ../../source/client/clientstart.cpp ../../network/socket/socket.h ../../network/formula/callpact.h
	  g++ -c ../../source/client/clientstart.cpp

#======================================================================clean objfile and exefile
clean_all:
	rm *.o
	rm clientstart

#----------------------------------------------------------------------clean exefile
clean_out:
	rm clientstart

#----------------------------------------------------------------------clean objfile
clean_obj:
	rm *.o
