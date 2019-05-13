mimic : mimic.o treap.o
	g++ -Wall -g mimic.o treap.o -o mimic

mimic.o: mimic.cc treap.h
	g++ -Wall -g -c mimic.cc -o mimic.o

treap.o: treap.cc treap.h
	g++ -Wall -g -c treap.cc -o treap.o

clean :
	rm -f mimic
	rm -f mimic.o
	rm -f treap.o
	rm -fr mimic.dSYM
