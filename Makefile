CC=gcc
OPT=-O3 -pedantic -Wall
DESTDIR=/usr/bin

strpftime: strpftime.c
	$(CC) $(OPT) -o strpftime strpftime.c 

clean:  
	rm -f *.o strpftime core strpftime_stream

install: strpftime
	install -m 755 strpftime $(DESTDIR)
