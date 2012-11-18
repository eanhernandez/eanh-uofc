Ean Hernandez - username: eanh - cspp51081 - lab 3 - 10-20-2010

filecopy.c, a file copying program.

filecopy accepts two args: an input file and an output file.  it then
either creates or overwrites the output file with the contents of the
input file. if the user attempts to overwrite the input file, or gives
an input file that does not exist, an error message is given and the
program exits.  if there are any errors opening, reading or writing from
the files, and error message is given and the program exits.

usage: ./filecopy t1.txt t2.txt

makeing: note that the make file assumes a test script test.sh and and
input file t1.txt.  these are included in the submission.



