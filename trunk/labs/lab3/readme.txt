Ean Hernandez - username: eanh - cspp51081 - lab 3 - 10-20-2010

estat.c, a stat like program.

estat accepts one argument (a filename), and gathers all the basic data
that stat would report for that filename.  It handles regular files,
symbolic links, directories, and hard links exactly as stat would.

usage: ./estat <filename>

makeing: typing "make" will build the .c file and make it executable.

note that there are test scripts called by the makefile's test recipies.
Running "make test1" will call test.sh which will run estat and regular
stat against a symlink called slink and a hard link called hlink.
Running "make test2" will call test2.sh which will run estat and 
regular stat against estat.c and the directory "."  ...the latter should
work anywhere once the initial make has been run.

sample:

eanh@daydream:~/cspp51081/labs/lab3$ ./estat estat.c
  file: `estat.c'
  size: 4126          blocks: 16          io block: 65536      regular file
device: 17h/23d       Inode: 12170      links: 1
access: (0604/-rw----r--)   uid: (10628   /   eanh)    gid: (13000  /  cppcs)
access: 2010-10-20 16:06:23.911555000 -0500
modify: 2010-10-20 16:06:23.913556000 -0500
change: 2010-10-20 16:06:23.913557000 -0500
eanh@daydream:~/cspp51081/labs/lab3$ stat estat.c
  File: `estat.c'
  Size: 4126            Blocks: 16         IO Block: 65536  regular file
Device: 17h/23d Inode: 12170       Links: 1
Access: (0604/-rw----r--)  Uid: (10628/    eanh)   Gid: (13000/   cppcs)
Access: 2010-10-20 16:06:23.911555000 -0500
Modify: 2010-10-20 16:06:23.913556000 -0500
Change: 2010-10-20 16:06:23.913557000 -0500
eanh@daydream:~/cspp51081/labs/lab3$
        
