all: project

project: function.o 
	cc main.c function.o list.o -o project

function.o: list.o
	cc -c function.c list.o
list.o: 
	cc -c list.c

clear:
	rm -rf *o project 
