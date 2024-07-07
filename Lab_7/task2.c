#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *print(void *args)
{
  pthread_t id = pthread_self();
  for(int i=0; i<5; i++)
  {
    printf("Child Thraed id is = %lu\n", id);
  }
  return NULL;
}

int main()
{
  pthread_t child_thread;
  int result;
  result= pthread_create(&child_thread, NULL, print ,NULL);
  if(result==-1)
  {
    printf("ERROR in creating the Child Thread\n");
    exit(1);  
  }
  pthread_join(child_thread, NULL);
  return 0;
}
