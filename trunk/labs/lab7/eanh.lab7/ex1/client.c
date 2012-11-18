#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
struct mymsg {long msg_type;  char mytext[512];} mymsg;
void conv(char *msg, int size);
int main(int argc, char ** argv)
{
   struct mymsg mToSend, mReceived;
   int iup_key, iup_queue, idown_queue, idown_key;
   char user_input[512];

   iup_key = ftok("..", 'u');                            // get a key for up queue
   iup_queue = msgget(iup_key, 0777 | IPC_CREAT );       // create up queue
   idown_key = ftok("..", 'd');                          // get a key for down queue
   idown_queue = msgget(idown_key, 0777 | IPC_CREAT );   // create down queue
   if (errno != 0)                                       // error handling
   {
      printf ("error(%d): %s\n",errno,strerror(errno));
      return(0);
   }  
   while (1)
   {
      fgets (user_input, sizeof(user_input), stdin);
      strcpy(mToSend.mytext,user_input);
      mToSend.msg_type =(float) getpid();     
      msgsnd(iup_queue,&mToSend,sizeof(struct mymsg)-sizeof(long),0);
      if (strcmp(user_input, "shutdown\n")==0)
      {
         printf("bye!\n");
         return(0);
      }

     msgrcv(idown_queue, &mReceived, sizeof(struct mymsg)-sizeof(long),0,getpid());
      printf("received from server: %s",mReceived.mytext);

   }
      
    return 0;
}

