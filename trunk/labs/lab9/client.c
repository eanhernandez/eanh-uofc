// Ean Hernandez HW9 8 Dec 2010
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *msg);

int main(int argc, char *argv[])
{
    // setting up variables
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
   
    // error handling input
    if (argc < 3) {fprintf(stderr,"usage %s hostname port\n", argv[0]); exit(0); }

    // setting up socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { error("ERROR opening socket");}

    // getting pointer to a hostent 
    server = gethostbyname(argv[1]);
    if (server == NULL) { fprintf(stderr,"ERROR, no such host\n"); exit(0); }

    // zero filling is big the socket world...
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // setting up zer_addr
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    int keepRunning = 1;
    // looping until we get a "quit"
    while (keepRunning ==1)
    {
       printf("Please enter a word to spell check: ");
       fflush(stdin);                                 // flushing seemed to help here
       memset(buffer,0,256);
       fflush(stdin);                                 // flushing seemed to help here
       fgets(buffer,255,stdin);
       fflush(stdin);                                 // flushing seemed to help here

       n = write(sockfd,buffer,strlen(buffer));       // write to the socket
       if (strcmp(buffer,"quit\n")==0){keepRunning=0;}// quit case

       if (n < 0) error("ERROR writing to socket");   
       bzero(buffer,256);
       n = read(sockfd,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("%s\n",buffer);
    }
    printf("bye.\n");
    return 0;
}
void error(char *msg)
{
    perror(msg);
    exit(0);
}

