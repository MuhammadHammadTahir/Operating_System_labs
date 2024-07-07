#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
int main()
{
  pid_t pid;
  int pipefd[2];
  if(pipe(pipefd)==-1)
  {
    printf("ERROR! Failed to create the process");
    return -1;
  }

  pid=fork();
  if(pid==-1)
  {
    printf("Error in creating th child processs\n");
    return -1;
  }
  if(pid==0)
  {
    close(pipefd[0]); //close the reading end
    char ch ='a';
    for(int i=0;i<26;i++)
    {
      write(pipefd[1], &ch, sizeof(ch));
      printf("%c ",ch);
      ch=ch+1;
    }
    close(pipefd[1]);
    return 0;
  }
  else {
    wait(NULL);
    char ch;
    close(pipefd[1]);//close the writig end
    printf("\n");
    while(read(pipefd[0], &ch, sizeof(ch))>0)
    {
      ch=toupper(ch);
      printf("%c ", ch);
    }
    return 0;
  } 

  return 0;
}
