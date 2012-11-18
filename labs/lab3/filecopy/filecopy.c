/*

Ean Hernandez - username: eanh - cspp51081 - lab 3 - 10-20-2010 

filecopy.c, a file copying program.

*/ 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define bBUFFER   40
#define COPYMODE  00755
void problem(char*s);

int main(int argc, char *argv[])

{
   char buffer[bBUFFER];
   int iInputFileDescriptor, iOutputFileDescriptor, iBytesRead, iBytesWrote;

   if ((strcmp(argv[1],argv[2]))==0){problem("self overwrite");}

   iInputFileDescriptor=open(argv[1], O_RDONLY);
   iOutputFileDescriptor=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,COPYMODE);
   if (iInputFileDescriptor == -1 || iOutputFileDescriptor == -1){problem("opening files");}

   while ((iBytesRead=read(iInputFileDescriptor, buffer, bBUFFER))>0)
   {
      iBytesWrote = write(iOutputFileDescriptor, buffer, iBytesRead);
      if (iBytesWrote != iBytesRead)
      {
         problem("writing files");
      }
   }

   close(iOutputFileDescriptor);
   close(iInputFileDescriptor);
   printf("copyfile completed successfully.\n");
   exit(0);
}

void problem(char*s)
{
   printf("copyfile encountered a problem: %s, and will now quit.\n",s);
   printf("try not to take it personally.");
   exit(1);
}
