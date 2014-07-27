CC=gcc
OPT=-O3 -pedantic

strpftime: strpftime.c
	$(CC) $(OPT) -o strpftime strpftime.c 

clean:  
	rm -f *.o strpftime core
