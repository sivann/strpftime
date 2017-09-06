CC=gcc
OPT=-O3 -pedantic -g

strpftime: strpftime.c
	$(CC) $(OPT) -o strpftime strpftime.c 
clean:  
	rm -f *.o strpftime core strpftime_stream
