#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

void *print(void *argu)
{
  char *msg =(char *) argu;
  printf("%s\n", msg);
  return NULL;
}


int main()
{
  pthread_t thread_1, thread_2;
  int result;
  char st1[100],st2[100];
  printf("Enter 1st Message to be print : \n");
  fgets(st1, sizeof(st1), stdin);
  printf("Enter 2nd Message to be print : \n");
  fgets(st2, sizeof(st2), stdin);
  result= pthread_create(&thread_1, NULL, print, &st1);
  if(result==-1)
  {
    printf("Error in creating the thread_1\n");
    exit(1);
  }
  result = pthread_create(&thread_2, NULL, print, &st2);
  if(result==-1)
  {
    printf("Error in creating the thread_2\n");
    exit(1);  
  }
  pthread_join(thread_1 ,NULL);
  pthread_join(thread_2 , NULL);

  printf("Both threads complete their execution\n");

  return 0;
}
