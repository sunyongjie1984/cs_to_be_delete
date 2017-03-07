CC=gcc
CFLAG = -o

all : work 

work : workcrew.c queue.c control.c 
	$(CC) $(CFLAG) work workcrew.c queue.c control.c -lpthread 

clean :
	@rm a.out work
	@rm -f *.o





