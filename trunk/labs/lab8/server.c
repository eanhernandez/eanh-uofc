// Ean Hernandez 12-01-2010 HW8
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int checkSpelling(char*s);
void error(char *msg);

int main(int argc, char *argv[])
{
     // setting up variables
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     // checking input
     if (argc < 2) {fprintf(stderr,"ERROR, no port provided\n"); exit(1);}

     // creating socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) { error("ERROR opening socket");}

     // setting up struct for socket call
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     // binding
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
     {
         error("ERROR on binding");
     }

     // listening
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     // get socket file descriptor
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) {error("ERROR on accept");}

     bzero(buffer,256);

     // setting up variables 
     int keepRunning = 1;     // controls wait loop
     char tmp[255];           // stores the word for sending back to the client
     char* p;                 // used to find and kill trailing \n
     char returnText[256];    // full text to return to client

     // runs until the client sends "quit"
     while(keepRunning == 1)
     {
        n = read(newsockfd,buffer,255);      // waiting for data from client
        strcpy(tmp, buffer);                 // getting a copy of the word
        p = strchr(tmp,'\n');                //   
        if (p) {*p = '\0';}                  // clean out \n

        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s",buffer);

        // return based on spell check result
        if (checkSpelling(buffer) == 1)
        {
            sprintf(returnText, "The word %s is spelled correctly.",tmp);
        }
        else
        {
            sprintf(returnText, "The word %s is spelled incorrectly.",tmp);
        }


        n = write(newsockfd,returnText,strlen(returnText));    // send message to client
        if (n < 0) error("ERROR writing to socket");
        if (strcmp(buffer,"quit\n")==0) {keepRunning = 0;}     // quit if we are done
     }
     printf("bye.\n");
     return 0; 
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


