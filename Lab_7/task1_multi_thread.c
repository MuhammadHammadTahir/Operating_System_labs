#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *count(void *argu)
{
  printf("Printinhg the Numbers from 1 to 5:\n");
  for(int i=1; i<=5; i++)
  {
    printf("%d\n", i);
  }
  return NULL;
}

void *alpha(void *argu)
{
  char ch ='A';
  printf("Printing the Alphabates from A to J\n");
  for(int i=0;i<10;i++)
  {
    printf("%c\n", ch);
    ch= ch+1; 
  }
  return NULL;
}

int main()
{
  pthread_t thread_1, thread_2;
  int result= pthread_create(&thread_1, NULL, count, NULL);
  if (result==-1)
  {
    printf("ERROR! In creating the thread_1\n");
    exit(1);
  }
  result= pthread_create(&thread_2, NULL, alpha, NULL);
  if (result==-1)
  {
    printf("ERROR! In creating the thread_2\n");
    exit(1);
  }

  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);

  printf("BOTH threads complete their task\n");

  return 0;
}
