main: main.o String.o
	g++ -o main main.o String.o
main.o: main.cpp String.h
	g++ -c main.cpp
String.o: String.cpp String.h
	g++ -c String.cpp
clean:
	-rm main main.o String.o
