#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>

struct message
{
  long mytype;
  int num;
};

int main()
{
  key_t key =1234;
  int msgid;
  struct message message_rcv;

  msgid= msgget(key, 0); //no need of the flag creation

  if(msgid==-1)
  {
    perror("msgget");
    exit(1);
  }
  
  for(int i; i<5;i++)
  {
    int ret =msgrcv(msgid, &message_rcv, sizeof(message_rcv.num), 0, 0);
    if(ret==-1)
    {
      perror("msgrcv");
      exit(1);
    }

    printf("Square of recived %d is %d\n", message_rcv.num, message_rcv.num*message_rcv.num);
  }

  return 0;
}
