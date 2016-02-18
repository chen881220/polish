app: main.o node.o stack.o polish.o calc.o
	gcc -g -o app main.o node.o stack.o polish.o calc.o

CC=gcc
O_FLAGS=-g -c

calc.o: calc.c polish.h node.h
	$(CC) $(O_FLAGS) calc.c

main.o: main.c stack.h node.h
	$(CC) $(O_FLAGS) main.c

node.o: node.c node.h
	$(CC) $(O_FLAGS) node.c

stack.o: stack.c stack.h node.h
	$(CC) $(O_FLAGS) stack.c

polish.o: polish.c polish.h node.h
	$(CC) $(O_FLAGS) polish.c

clean:
	-rm *.o
