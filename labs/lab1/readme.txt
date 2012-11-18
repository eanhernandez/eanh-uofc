Ean Hernandez cspp51081 lab1 10/06/2010

exercises:

1.1, 1.2, 1.3 : see transcript_lab1.txt

1.4 The myfile is simply a file containing the text I put in it.
The soft_link is a symbolic link, and is a pointer to myfile:wq.  It is
smaller than the other files, because it merely points to the filename
of myfile.  The hard_link file is the same size as myfile because it
points to the same inode that myfile points to, and is literally another 
name for the data that myfile points to. 

2.1, 2.2, 2.3, 2.4, 2.5 : see transcript_lab1.txt

3. stat indicates that this is a 4096k directory in which the owner may
read write and execute, group members may read and execute, and everyone
may read and execute.  It was last modified on january 27 this year,
and was last accessed on the 6th of this month.  ls -al | grep '^d' |
nl  shows there are 29 directories in ~mark/pub/51081 plus the . and
.. directories representing 51081 and it's parent pub.  Subtracting this
amount from the total number of files returned by ls -al | nl gives us
71-2-29 = 40 files.




