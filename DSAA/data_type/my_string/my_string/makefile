main: main.o my_string.o
	g++ -o main main.o my_string.o
main.o: main.cpp my_string.h
	g++ -c main.cpp
my_string.o: my_string.cpp my_string.h
	g++ -c my_string.cpp
clean:
	-rm main main.o my_string.o
