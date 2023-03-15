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

test_static_O0:
	make clean
	$(CC) $(FLAGS) -O0 -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o
	$(CC) $(FLAGS) -O0 main.c -o main -L. -l$(SOURCE_NAME)
	cat ./commands.txt | ./main > ./result_static_O0.txt


test_static_O2:
	make clean
	$(CC) $(FLAGS) -O2 -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o
	$(CC) $(FLAGS) -O2 main.c -o main -L. -l$(SOURCE_NAME)
	cat ./commands.txt | ./main > ./result_static_O2.txt

test_static_Os:
	make clean
	$(CC) $(FLAGS) -Os -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o
	$(CC) $(FLAGS) -Os main.c -o main -L. -l$(SOURCE_NAME)
	cat ./commands.txt | ./main > ./result_static_Os.txt

test_shared_O0:
	make clean
	$(CC) -fPIC $(FLAGS) -O0 -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -O0 -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) -O0 main.c -o main -L. -l$(SOURCE_NAME) -Wl,-rpath,.
	cat ./commands.txt | ./main > ./result_shared_O0.txt

test_shared_O2:
	make clean
	$(CC) -fPIC $(FLAGS) -O2 -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -O2 -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) -O2 main.c -o main -L. -l$(SOURCE_NAME) 	-Wl,-rpath,.
	cat ./commands.txt | ./main > ./result_shared_O2.txt

test_shared_Os:
	make clean
	$(CC) -fPIC $(FLAGS) -Os -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -Os -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) -Os main.c -o main -L. -l$(SOURCE_NAME) -Wl,-rpath,.
	cat ./commands.txt | ./main > ./result_shared_Os.txt

test_dynamic_O0:
	make clean
	$(CC) -fPIC $(FLAGS) -O0 -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -O0 -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) -O0 main.c -ldl -D DYNAMIC -o main
	cat ./commands.txt | ./main > ./result_dynamic_O0.txt

test_dynamic_O2:
	make clean
	$(CC) -fPIC $(FLAGS) -O2 -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -O2 -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) -O2 main.c -ldl -D DYNAMIC -o main
	cat ./commands.txt | ./main > ./result_dynamic_O2.txt

test_dynamic_Os:
	make clean
	$(CC) -fPIC $(FLAGS) -Os -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -fPIC $(FLAGS) -Os -shared -o $(LIB_NAME).so $(LIB_NAME).o
	$(CC) $(FLAGS) -Os main.c -ldl -D DYNAMIC -o main
	cat ./commands.txt | ./main > ./result_dynamic_Os.txt


test_static:
	make test_static_O0
	make test_static_O2
	make test_static_Os

test_shared:
	make test_shared_O0
	make test_shared_O2
	make test_shared_Os

test_dynamic:
	make test_dynamic_O0
	make test_dynamic_O2
	make test_dynamic_Os

all_tests:
	make test_static
	make test_shared
	make test_dynamic
	make clean

clean_all:
	make clean
	rm -f ./result_*.txt

