#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <mqueue.h>

struct mymsg {long msg_type;  char mytext[512];} mymsg;
void conv(char *msg, int size);
int main(int argc, char ** argv)
{
   struct mymsg m;
   int iup_key, iup_queue, idown_queue, idown_key;
   iup_key = ftok("..", 'u');
   iup_queue = msgget(iup_key, 0777 | IPC_CREAT );
   idown_key = ftok("..", 'd');
   idown_queue = msgget(idown_key, 0777 | IPC_CREAT );

   while (1)
   {
      msgrcv(iup_queue, &m, sizeof(struct mymsg)-sizeof(long), 0, 0);
      printf("received from %ld: %s", m.msg_type,m.mytext);
      if (strcmp(m.mytext,"shutdown\n")==0)
      {
         strcpy(m.mytext,"shutdown request received, closing queue.\n");
         printf("%s\n",m.mytext);
         break;
      }
      else
      {
         conv (m.mytext,sizeof(mymsg.mytext));
         msgsnd(idown_queue,&m,sizeof(struct mymsg)-sizeof(long),IPC_NOWAIT);
         printf("sent %s", m.mytext);
     }
  }   
  msgctl(iup_queue, IPC_RMID,NULL );
  msgctl(idown_queue, IPC_RMID,NULL);
 
  return 0;
}
void conv(char *msg, int size)
{
   int i;
   for (i=0; i<size; ++i)
   {
      if (islower(msg[i]))
      msg[i] =  toupper(msg[i]);
      else if (isupper(msg[i]))
      msg[i] =  tolower(msg[i]);
   } 
}

