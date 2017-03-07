all: ls1 hello testerror seek
ls1 ls1.c
	g++ -g -Wall ls1.c ../lib/libapue.a -I ../include -o ls1
hello: hello.c
	g++ -g -Wall hello.c -I ../include/ ../lib/libapue.a -o hello
testerror: testerror.c
	g++ -g -Wall testerror.c -I ../include/ ../lib/libapue.a -o testerror
seek: seek.c
	g++ -g -Wall seek.c -I ../include/ ../lib/libapue.a -o seek
clean:
	rm ls1 hello testerror seek
