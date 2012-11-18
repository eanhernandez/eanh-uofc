Ean Hernandez

transcript...

eanh@daydream:~/classes/unix/labs/lab5/ean.lab5/ex3$ ./my_npipe_writer
I'm a writer.  I write things.
test line 1
wrote 256 bytes
test line 2
wrote 256 bytes
test line 3
wrote 256 bytes
exit
bye!
eanh@daydream:~/classes/unix/labs/lab5/ean.lab5/ex3$


eanh@daydream:~/classes/unix/labs/lab5/ean.lab5/ex3$ ./my_npipe_reader
I'm a reader.  I read things.
making fifo returns 0
writer wrote: test line 1
writer wrote: test line 2
writer wrote: test line 3
bye!
eanh@daydream:~/classes/unix/labs/lab5/ean.lab5/ex3$

