CFLAGS=-Wall -std=gnu99
CC=gcc

filecopy : filecopy.o

clean : 
	rm -f filecopy.o test.sh makefile filecopy t1.txt t2.txt

test : filecopy.c test.sh t1.txt
	./test.sh
