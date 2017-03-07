CFLAGS = -Wall -g
ALL = tcpserv01 tcpserv02 tcpcli01 tcpcli07

all: ${ALL}

tcpserv01.o: tcpserv01.cpp
	g++ ${CFLAGS} -c -o tcpserv01.o tcpserv01.cpp -I ../../lib
tcpserv01: tcpserv01.o
	g++ ${CFLAGS} -o tcpserv01 tcpserv01.o ../../libunp.a -I ../../lib

sigchldwait.o: sigchldwait.cpp
	g++ ${CFLAGS} -c -o sigchldwait.o sigchldwait.cpp -I ../../lib

tcpserv02.o: tcpserv02.cpp
	g++ ${CFLAGS} -c -o tcpserv02.o tcpserv02.cpp -I ../../lib
tcpserv02: tcpserv02.o sigchldwait.o
	g++ ${CFLAGS} -o tcpserv02 tcpserv02.o sigchldwait.o ../../libunp.a -I ../../lib

tcpcli01.o:tcpcli01.cpp
	g++ ${CFLAGS} -c -o tcpcli01.o tcpcli01.cpp -I ../../lib
tcpcli01: tcpcli01.o
	g++ ${CFLAGS} -o tcpcli01 tcpcli01.o ../../libunp.a -I ../../lib

tcpcli07.o:tcpcli07.cpp
	g++ ${CFLAGS} -c -o tcpcli07.o tcpcli07.cpp -I ../../lib
tcpcli07: tcpcli07.o
	g++ ${CFLAGS} -o tcpcli07 tcpcli07.o ../../libunp.a -I ../../lib

clean:
	rm *.o ${ALL}
