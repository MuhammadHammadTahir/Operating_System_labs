#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void *space_allocate(void *args)
{
  char large_arry[1000000000];
  for(int i=0; i<10000000000; i++)
  {
    large_arry[i]='a';
  }
  return NULL;
}

int main()
{
  int result;
  pthread_t thread;
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  
  size_t size=100000000000;
  pthread_attr_setstacksize(&attr, size);

  result=pthread_create(&thread, &attr, space_allocate, NULL);
  if(result==-1)
  {
    printf("Error in creating the thread\n");
    exit(1);
  }
  pthread_join(thread, NULL);
  return 0;
}
