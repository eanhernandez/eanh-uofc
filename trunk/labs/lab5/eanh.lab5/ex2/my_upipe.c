/*
Ean Hernandez lab5 part 2

upipe.c - a low level pipe ripoff
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void tokenize_input(char* argv, char** args_tokenized);
void show_input(char**a);
int main(int argc, char**argv)
{
   if (argc!=3){printf("requires two args separated by quotes\n"); exit(1);}

   char argv1_copy[80];                // stores first set of args so strtok can eat them
   char argv2_copy[80];                // stores second set of args so strtok can eat them
   strcpy(argv1_copy,argv[1]);         // make copy
   strcpy(argv2_copy,argv[2]);         // make copy
   //show_input(argv);                 // debugging
   char *argv1_tokenized[20];          // stores first arg set once tokenized
   char *argv2_tokenized[20];          // stores second arg set once tokenized
   tokenize_input(argv1_copy,argv1_tokenized);
   tokenize_input(argv2_copy,argv2_tokenized);
   printf("exit status: %d",simple_fork_command(argv1_tokenized,argv2_tokenized));
   exit(0);
}

void show_input(char**a)               // for debugging
{  
   int i;
   for (i=0;i<sizeof(a);i++)
   {
      printf("arg %d: %s\n",i,a[i]);
   }
}

int simple_fork_command(char** childArgs, char ** parentArgs)  // the easy part
{
   int pid;       
   int exitstatus;
   int pfd[2];
   pipe(pfd);

   pid = fork();
   if (pid == 0)
   {
      //child
      close(pfd[0]);
      dup2(pfd[1],1);
      printf("return val child: %d\n",execvp(childArgs[0],childArgs));
      fflush(stdout);
   }
   else
   {
      //parent
      close(pfd[1]);
      dup2(pfd[0],0);
      printf("return val parent: %d\n",execvp(parentArgs[0],parentArgs));
      wait(&exitstatus);
      fflush(stdout);
   }
   return(exitstatus);
}

void tokenize_input(char* argv_local, char** args_tokenized) // the HARD part!
{
   {
    char* p = strchr(argv_local,'\n');
    if (p) {*p='\0';}
    char* splitter = " ";
    int i=0;
    char*token[80];
    token[0]=strtok(argv_local,splitter);
    args_tokenized[0]=token[0];
    while(token[i] != NULL)
    {
      i++;
      token[i]=strtok(NULL,splitter);
      args_tokenized[i]=token[i];
    }
   }
}
