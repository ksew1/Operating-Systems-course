CC = gcc
FLAGS = -Wall
LIB_NAME = libmylib
SOURCE_NAME = mylib

static:
	make clean
	$(CC) $(FLAGS) -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o
	$(CC) $(FLAGS) main.c -o main -L. -l$(SOURCE_NAME)

shared:
	make clean
	$(CC) -fPIC $(FLAGS) -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) main.c -o main -L. -l$(SOURCE_NAME) -Wl,-rpath,.

dynamic:
	make clean
	$(CC) -fPIC $(FLAGS) -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS)  main.c -ldl -D DYNAMIC -o main

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main