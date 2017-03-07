CC=g++
CFLAG = -o

all : work

work : work.c queue.c control.c ../sync.cpp 
	$(CC) $(CFLAG) work work.c queue.c control.c ../sync.cpp  -lpthread

clean :
	@rm work 
	@rm -f *.o





