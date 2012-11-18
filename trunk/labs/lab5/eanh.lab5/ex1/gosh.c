//Ean Hernandez HW5
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int simple_fork_command(char** a);
void get_input(char* user_input, char** args);
int parse_input(char* user_input, char** args);
char*line="-----------------------";

int main() 
{
   char* args[80];
   char user_input[80];
   char user_input_copy[80];
   int exitstatus; 
   char* cwd;
   char*to;
   int p_i=0;
   while(1) 
   {
      printf("gosh> ");                                // command prompt
      fgets (user_input, sizeof(user_input), stdin);   // get input from user
      strcpy(user_input_copy,user_input);              // make copy bc strtok eats original
      get_input(user_input_copy,args);                 // tokenize the input
      p_i=parse_input(user_input,args);                // figure out what the user wants to do
      exitstatus = 0;

      switch(p_i)
      {
        case 1: //quitting
            printf("bye!\n"); exit(0); break;
        case 2: //erroneous cr
            break;
        case 3: //cd
            printf("Running Command\n%s\n",line);
            exitstatus = chdir(args[1]);
            printf("Change Dir:");
            if (exitstatus == 0){printf("success\n");}else{printf("failed!\n");}
            printf("%s\n",line);
            break;
        case 4: //pwd
            printf("Running Command\n%s\n",line);
            cwd = get_current_dir_name();
            printf("%s\n",cwd);
            printf("%s\n",line);
            break;
        case 5: //set env
            printf("Running Command\n%s\n",line);
            printf("setenv returns: %d\n",setenv(args[0],args[1],1));
            printf("%s\n",line);
            break;
        case 6: //get env
            printf("Running Command\n%s\n",line);
            to = malloc(strlen(args[1]));                
            strncpy(to, args[1]+1, strlen(args[1]));
            printf("%s = %s\n",args[1],getenv(to));
            free(to);
            printf("%s\n",line);
            break;
        default: //execute a command in child
            printf("Running Command\n%s\n",line);
            exitstatus = simple_fork_command(args);
            printf("%s\nCommand Returned Exit Code %d\n",line,exitstatus);
       }
    }
}

int parse_input(char*u, char**a)
{     
   char* p = strchr(u,'\n');
   if (p) {*p='\0';}

   if (u[0]=='\0'){return 2;}                            // errant CR   = 2
   if (strcmp(a[0],"exit")==0){return 1;}                // quitting    = 1
   if (strcmp(a[0],"cd")==0){return 3;}                  // change dir  = 3
   if (strcmp(a[0],"pwd")==0){return 4;}                 // pwd request = 4
   if (strchr(u,'=')){return 5;}                         // =sign,setenv= 5
   if (strchr(u,'$')){return 6;}                         // $, get env  = 6
   return 999;                                           // command     = 999
}

void get_input(char* user_input, char** args)
{

      char* p = strchr(user_input,'\n');
      char* splitter = " =";
      if (p) {*p='\0';}
      if (strchr(user_input,'\'')){splitter="=";}
      int i=0;
      char*token[80];
      token[0]=strtok(user_input,splitter);
      args[0]=token[0];

      while(token[i] != NULL)
      {
         i++;
         token[i]=strtok(NULL,splitter);
         args[i]=token[i];
      }
}
int simple_fork_command(char** f)
{
      int pid;
      int exitstatus;
      pid = fork();
      
      if (pid == 0)
      {
            printf("return val child: %d\n",execvp(f[0],f));
            fflush(stdout);
      }
      else
        {
            wait(&exitstatus);
            fflush(stdout);
         }
   return(exitstatus);
}
