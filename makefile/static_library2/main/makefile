main: main.cpp libstr.a
	g++ -o main -I ../str main.cpp ../lib/libstr.a

libstr.a: ../str/Strlen.o ../str/Strlnen.o
	ar -rc ../lib/libstr.a ../str/Strlen.o ../str/Strlnen.o

Strlen.o: ../str/Strlen.cpp
	g++ -c ../str/Strlen.cpp

Strlnen.o: ../str/Strlnen.cpp
	g++ -c ../str/Strlnen.cpp

clean:
	rm main ../lib/libstr.a ../str/Strlen.o ../str/Strlnen.o
