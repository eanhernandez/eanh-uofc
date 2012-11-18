#Ean Hernandez cspp51081 12-08-2010 LAB9
LDFLAGS=-static -Wl,-rpath=/opt/glibc/glibc-2.2.2/lib
INCLDIR=-I/opt/glibc/glibc-2.2.2/include
LIBDIR=-L/opt/glibc/glibc-2.2.2/lib
LIBS=-lpthread

CFLAGS=-Wall -std=gnu99 -lm
CC=gcc

all : client server

client : client.o 
			${CC} ${LDFLAGS} -o $@ $@.c ${LIBS} ${LIBDIR} ${INCLDIR} 

server : server.o 
			${CC} ${LDFLAGS} -o $@ $@.c ${LIBS} ${LIBDIR} ${INCLDIR}

clean : 
			rm -f *.o client server

