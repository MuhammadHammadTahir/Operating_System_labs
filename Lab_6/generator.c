#include <stdio.h>
#include <unistd.h>
int main()
{
  int pipefd[2];
  char ch='a';
  if(pipe(pipefd)==-1)
  {
    printf("ERROR! FAILED TO CREATE THE PIPE\n");
    return -1;
  }

  for(int i=0;i<26;i++)
  {
    //printf("%c\n",ch);
    write(pipefd[1], &ch , sizeof(ch));
    ch=ch+1;
    //:sleep(1);
  }

 // while(1)
  //{

  //}

  //close(pipefd[1]);
  return 0;
}
