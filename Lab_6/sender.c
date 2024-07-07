#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

struct message{
  long mytype;
  int num;
};

int main()
{
  key_t key=1234;
  int msgid;
  msgid =msgget(key, IPC_CREAT|0666);
  if(msgid ==-1)
  {
    perror("msgget");
    exit(1);
  }

  struct message messages[] ={
    {1,1},
    {1,2},
    {1,3},
    {1,4},
    {1,5}
  };

  int num_message=sizeof(messages)/sizeof(messages[0]);

  for(int i=0 ;i<num_message; i++)
  {
    int ret = msgsnd(msgid, &messages[i], sizeof(messages[i].num), 0);
    if(ret==-1)
    {
      perror("msgsnd");
      exit(1);
    }
    printf("Producer sent %d message\n", messages[i].num);
  }

 // msgctl(msgid, IPC_RMID, NULL);
  printf("Producer finished sending messages.\n");

  return 0;
}
