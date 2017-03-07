main : main.o account.o
	g++ -g -o main main.o account.o
main.o : main.cpp
	g++ -g -c main.cpp
account.o : account.cpp
	g++ -g -c account.cpp
clean:
	-rm main main.o account.o
