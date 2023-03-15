CC = gcc -Wall
P = ../
all:
	make clean
	$(CC) main.c -o main
	./main $(P)

clean:
	rm -f main

run_command:
	find $(P) | xargs wc --bytes
