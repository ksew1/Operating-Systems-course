CC = gcc -Wall
IN = ./main.c
OUT = ./output.txt
C1 = a
C2 = b
compile_f:
	make clean
	$(CC) -o  main main.c
compile_s:
	make clean
	$(CC) -o  main main.c -D USESYS


run_f:
	make compile_f
	echo "LIB: " > pomiar_zad_1.txt
	./main $(C1) $(C2) $(IN) $(OUT) >> pomiar_zad_1.txt
run_s:
	make compile_s
	echo "\nSYS: " >> pomiar_zad_1.txt
	./main $(C1) $(C2) $(IN) $(OUT) >> pomiar_zad_1.txt

clean:
	rm -f main
	rm -f tmp
	rm -f $(OUT)

compare:
	./main $(C1) $(C2) $(IN) $(OUT)
	tr $(C1) $(C2) < $(IN) > tmp
	diff -s tmp $(OUT)

test_f:
	make compile_f
	make compare

test_s:
	make compile_s
	make compare

test:
	make test_f
	make test_s

all:
	make run_f
	make run_s