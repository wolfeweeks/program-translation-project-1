scanner: main.o scanner.o
	gcc main.o scanner.o -o scanner

main.o: main.c
	gcc -c main.c

scanner.o: scanner.c
	gcc -c scanner.c
	
clean:
	rm -rf ./scanner *.o