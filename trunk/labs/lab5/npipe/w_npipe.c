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
   int fd, iBytesWrote;
   fd=open("local_named_pipe", 0666 );
   if (errno != 0){printf ("error(%d): %s\n",errno,strerror(errno));}
   printf("I'm a writer.  I write things.\n");
   while(1)
   {
      fgets (foo, sizeof(foo), stdin);
      if (strcmp(foo,"exit\n")==0)
      {
         write(fd, "exit", sizeof("exit"));
         printf("bye!\n");
         close(fd);
         exit(0);
      }
     printf("wrote %d bytes\n",iBytesWrote = write(fd, foo, sizeof(foo)));
   }
}
