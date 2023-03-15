CC = gcc -Wall


compile_1:
	make clean
	$(CC) -o  main main.c -D BUFFER_SIZE=1

compile_1024:
	make clean
	$(CC) -o  main main.c -D BUFFER_SIZE=1024

run:
	./main ./input.bin ./tmp1.bin >> pomiar_zad_2.txt
	echo "REVERSING" >> pomiar_zad_2.txt
	./main ./tmp1.bin ./tmp2.bin >> pomiar_zad_2.txt
	diff -s ./tmp2.bin ./input.bin


test:
	echo "TESTING WITH BUFFER_SIZE = 1" > pomiar_zad_2.txt
	make compile_1
	make run
	echo "\nTESTING WITH BUFFER_SIZE = 1024" >> pomiar_zad_2.txt
	make compile_1024
	make run

clean:
	rm -f main
	rm -f tmp1.bin
	rm -f tmp2.bin

