CC = gcc -Wall
all:
	$(CC) -o main main.c

test: all
	./main /bin
	./main ./
	./main ./empty_dir/

clean:
	rm -f main