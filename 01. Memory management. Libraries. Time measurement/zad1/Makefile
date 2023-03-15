CC = gcc
FLAGS = -Wall
LIB_NAME = libmylib
SOURCE_NAME = mylib


static:
	make clean
	$(CC) $(FLAGS) -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o


shared:
	make clean
	$(CC) -fPIC $(FLAGS) -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -shared -o $(LIB_NAME).so $(LIB_NAME).o


clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main