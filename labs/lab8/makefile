#Ean Hernandez cspp51081 12-01-2010 LAB8
CFLAGS=-Wall -std=gnu99 -lm
CC=gcc

all : client server

client : client.o 
			$(CC) -o $@ $< $(CFLAGS)

server : server.o 
			$(CC) -o $@ $< $(CFLAGS)

clean : 
	rm -f *.o client server

