Ean Hernandez

transcript...

eanh@daydream:~/classes/unix/labs/lab5/egosh$ ./gosh
gosh> ls -a -l -d /etc
Running Command
-----------------------
drwxr-xr-x 173 root root 9840 2010-11-10 15:03 /etc
-----------------------
Command Returned Exit Code 0
gosh>
gosh>
gosh>
gosh>
gosh> ls -l /etc/passwd
Running Command
-----------------------
-rw-r--r-- 1 root root 1577 2010-10-12 12:37 /etc/passwd
-----------------------
Command Returned Exit Code 0
gosh> cd /usr/lib
Running Command
-----------------------
Change Dir:success
-----------------------
gosh> pwd
Running Command
-----------------------
/usr/lib
-----------------------
gosh> MYVAR='All work and no play makes Jack a dull boy'
Running Command
-----------------------
setenv returns: 0
-----------------------
gosh> echo $MYVAR
Running Command
-----------------------
$MYVAR = 'All work and no play makes Jack a dull boy'
-----------------------
gosh> exit
bye!
eanh@daydream:~/classes/unix/labs/lab5/egosh$

