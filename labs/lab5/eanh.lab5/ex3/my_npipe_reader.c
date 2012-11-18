// Ean Hernandez HW5
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char**argv)
{

   char foo[256];
   char buffer[256];
   int fd, iBytesRead;
   printf("I'm a reader.  I read things.\n");
   printf("making fifo returns %d\n",mkfifo("local_named_pipe",0666));
   if (errno != 0){printf ("error(%d): %s\n",errno,strerror(errno));}

   fd = open("local_named_pipe", O_RDONLY);
   if (errno != 0){printf ("error(%d): %s\n",errno,strerror(errno));}


   while (1)
   {
      usleep(1000000 * 4);  
      iBytesRead=(read(fd, buffer, 256));
      if (iBytesRead > 0)
      {
        if (strcmp(buffer,"exit")==0)
        {
           printf("bye!\n");
           close(fd);
           exit(0);
        }
        else
        {
            printf("writer wrote: %s",buffer);
        }
      }
   }
   printf("read 0, so closing!\n");
}
