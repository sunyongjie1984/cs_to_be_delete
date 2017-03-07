all: shell1 shell2 fork1 vfork1 wait1 fork2
shell1: shell1.c
	g++ -g -Wall shell1.c ../lib/libapue.a -I ../include -o shell1
shell2: shell2.c
	g++ -g -Wall shell2.c ../lib/libapue.a -I ../include -o shell2
fork1: fork1.c
	g++ -g -Wall fork1.c ../lib/libapue.a -I ../include -o fork1
fork2: fork2.c
	g++ -g -Wall fork2.c ../lib/libapue.a -I ../include -o fork2
vfork1: vfork1.c
	g++ -g -Wall vfork1.c ../lib/libapue.a -I ../include -o vfork1
wait1: wait1.c
	g++ -g -Wall wait1.c ../lib/libapue.a -I ../include -o wait1
clean:
	rm shell1 shell2 fork1 vfork1 wait1 fork2
