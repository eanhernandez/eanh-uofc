// Ean Hernandez 12-08-2010 HW9
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
int checkSpelling(char*s);
void error(char *msg);
void *doThread(void *fp);
int main(int argc, char *argv[])
{
     // checking input
     if (argc < 2) {fprintf(stderr,"ERROR, no port provided\n"); exit(1);}

     // setting up variables
     int sockfd, portno, newsockfd;
     struct sockaddr_in serv_addr;
     int *fdptr;
     pthread_attr_t *attr;
     pthread_t worker;

     // creating socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) { error("ERROR opening socket");}

     // setting up struct for socket call
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     //setting up thread attributes
     attr=(pthread_attr_t*)malloc(sizeof(pthread_attr_t));
     pthread_attr_init(attr);
     pthread_attr_setdetachstate(attr,PTHREAD_CREATE_DETACHED);

     // binding
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
     {
         error("ERROR on binding");
     }

     // listening
     listen(sockfd,5);
     printf("ready to spell check.\n");
     while(1)
     {
        newsockfd = accept(sockfd, NULL, NULL);
        if (newsockfd < 0) {error("ERROR on accept");}
        printf("received connection, spawning thread...\n");
        fdptr = malloc(sizeof(int));
        *fdptr = newsockfd;
        pthread_create(&worker,attr,doThread,fdptr);
     }
     return 0; 
}

void *doThread(void *fdptr)
{    
        int n,fd;
        char buffer[256];
        char tmp[255];           // stores the word for sending back to the client
        char* p;                 // used to find and kill trailing \n
        char returnText[256];    // full text to return to client
        int keepGoing = 1; 
        fd = *(int*)fdptr;
        free(fdptr);

        while(keepGoing==1)
        {
          memset(buffer,0,256);
          n = read(fd,buffer,255);      // waiting for data from client
          strcpy(tmp, buffer);                 // getting a copy of the word
          p = strchr(tmp,'\n');                //   
          if (p) {*p = '\0';}                  // clean out \n

          if (n < 0){error("ERROR reading from socket"); }
          if (strcmp(tmp,"quit")==0){ keepGoing = 0; } 

          printf("received word to spellcheck: %s",buffer);
          // return based on spell check result
          if (checkSpelling(buffer) == 1)
          {
              printf("Correct spelling, notifying client.\n");
              sprintf(returnText, "The word %s is spelled correctly.",tmp);
          }
          else
          {
              printf("Incorrect spelling, notifying client.\n");
              sprintf(returnText, "The word %s is spelled incorrectly.",tmp);
          }

          n = write(fd,returnText,strlen(returnText));    // send message to client
          if (n < 0) {error("ERROR writing to socket");}
        }
        
        printf("received quit signal, terminating thread.\n");
        fflush(stdout);
        return NULL;                                     //no idea why gcc makes me do this
}

// checks spelling file for s
int checkSpelling(char*s)
{
   FILE *fp=fopen("/usr/share/dict/words","r");
   char tmp[256];
   while(fp!=NULL && fgets(tmp, sizeof(tmp), fp)!=NULL)
   {
      if (strcmp(tmp, s)==0){ return 1;}
   }
   return 0;
   fclose(fp);
}

// error messages
void error(char *msg)
{
    perror(msg);
    exit(1);
}

