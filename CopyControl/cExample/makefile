main: main.o example.o
	g++ -g -o main main.o example.o
main.o: main.cpp
	g++ -g -c main.cpp
example.o: example.cpp example.h
	g++ -g -c example.cpp
clean:
	rm main.o example.o main
