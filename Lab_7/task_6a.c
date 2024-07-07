#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *space_allocate(void *args)
{
  char large_arry[10000000000];
  for(int i=0; i<10000000000; i++)
  {
    large_arry[i]='a';
  }
  return NULL;
}
int main()
{
  pthread_t thread;
  int result;
  result=pthread_create(&thread, NULL, space_allocate, NULL);
  if(result==-1)
  {
    printf("Error in creating thread\n");
    exit(1);
  }

  pthread_join(thread, NULL);

  return 0;
}
