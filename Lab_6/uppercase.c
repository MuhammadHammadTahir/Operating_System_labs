#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
  int pipefd[2];
  char ch;
  
  if(read(pipefd[0], &ch , sizeof(ch))==-1)
  {
    printf("Error! Failed to read the pipe");
    return -1;
  }
  printf("Hello\n");

  while(read(pipefd[0], &ch , sizeof(ch))>0)
  {
    printf("%c\n",ch);
    ch=toupper(ch);
    printf("%c\n",ch);
  }

  close(pipefd[0]);
  return 0;
}
