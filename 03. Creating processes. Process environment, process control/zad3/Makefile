CC = gcc -Wall
all:
	$(CC) -o main main.c

test: all
	./main . "#include"
	./main .. "#include"
	./main ../.. "#include"

	./main . asdf
	./main .. asdf
	./main ../.. asdf

	./main . zadanie
	./main .. zadanie
	./main ../.. zadanie


clean:
	rm -f main