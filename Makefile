#Makefile
all: sum-nbo

test: sum-nbo
	echo -n -e \\x00\\x00\\x03\\xe8 > thousand.bin
	echo -n -e \\x00\\x00\\x01\\xf4 > five-hundred.bin
	echo -n -e \\x00\\x00\\x00\\xc8 > two-hundred.bin

sum-nbo: main.o 
	g++ -o sum-nbo main.o 

main.o: main.c
	g++ -c -o main.o main.c
	
clean:
	rm -f sum-nbo
	rm -f *.o
	rm -f *.bin
