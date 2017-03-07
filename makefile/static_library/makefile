main: main.cpp libstr.a
	g++ -o main main.cpp libstr.a

libstr.a: Strlen.o Strlnen.o
	ar -rc libstr.a Strlen.o Strlnen.o

Strlen.o: Strlen.cpp
	g++ -c Strlen.cpp

Strlnen.o: Strlnen.cpp
	g++ -c Strlnen.cpp

clean:
	rm *.o *.a main
