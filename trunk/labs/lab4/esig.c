/*
Ean Hernandez cspp51081 10-27-2010 LAB 4

esig.c, a signal handling program.

this program accepts a single argument , which must be a number, and does
input validation on the argument.  Passing these tests, it will become
the ceiling allowed for CTRL-C to be signalled to this program.  the program
then registers signal handlers for SIGINT and SIGUSR1, and enters a loop
where it waits.  when either signal is sent, appropriately spooky halloween
text is printed to the screen, and in the case of SIGINT, a counter is
incremented. if the counter is not less than the value specified in the 
argument from the command line, the program exits.
*/


#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int sigIntCount = 0;
int maxAllowedSigints = 0;
void gotSigInt(int signal);
void gotSigUsr1(int signal);

int main(int argc, char* argv[])
{

   if (argc != 2) {printf("just one arg please.\n");exit(0);}
   for(int i=0;i<strlen(argv[1]);i++)
   {  
      if (((int)argv[1][i]<48)||((int)argv[1][i]>57)) //allows 0-9 only 
         {  
            printf("input must be numbers only.\n");exit(0);
         }
   }

   printf("signal handling (halloween version).\n");

   maxAllowedSigints = atoi(argv[1]);

   signal(SIGINT, gotSigInt);
   signal(SIGUSR1, gotSigUsr1);
   while(1)
   {
     sleep(1000000 * 4); 
   }
}

void gotSigUsr1(int signal)
{
   printf("\nfoolish human, not even SIGUSR1 can stop me!\n");
   fflush(stdout);
}


void gotSigInt(int signal)
{
   sigIntCount++;
   if(sigIntCount >= maxAllowedSigints)
   {     
      printf("\nok, you got me, I'm just a guy in pancake makeup with a fake accent and a copy of signal.\n");
      exit(0);
   }
   else
   {
      printf("\nyou've pressed CTRL-C %d times... how can you kill that which is not alive?!",sigIntCount);
   }
   fflush(stdout);
}

