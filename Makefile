project: main.o function.o list.o queue.o stack.o  
	gcc main.o function.o list.o queue.o stack.o -o project

main.o: main.c list_stack.h
	gcc -c main.c
		 
function.o : function.c queue.h list_stack.h 
	gcc -c function.c
	
list.o : list.c list_stack.h
	gcc -c list.c

queue.o : queue.c queue.h
	gcc -c queue.c

stack.o : stack.c list_stack.h
	gcc -c stack.c

clear : 
	rm -rf *o project

