#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

void *prep_pop(void *)
{
  printf("Preparing the popcons.....\n");
  sleep(2);
  printf("Popcon has prepared.....\n");
}

void *prep_soda(void *)
{
  printf("Preparing the soda......\n");
  sleep(1);
  printf("Soda is prepared.....\n");
}

void *prep_candy(void *)
{
  printf("Preparing the Candy......\n");
  sleep(3);
  printf("Candy is Prepared........\n");
}


void *take_order(void *)
{
  int random= rand()%3+1;
  if(random==1)
  {
    int result2;
    pthread_t thread_pop;
    result2= pthread_create(&thread_pop, NULL, prep_pop, NULL);
    if(result2==-1)
    {
      printf("Error in creating the thread of popcon\n");
      exit(1);
    }
  }
  else if(random==2)
  {
    int result3;
    pthread_t thread_soda;
    result3= pthread_create(&thread_soda, NULL, prep_soda, NULL);
    if(result3==-1)
    {
      printf("Error in creating the thread of soda\n");
      exit(1);
    }
  }
  else if(random==3)
  {
    int result4;
    pthread_t thread_candy;
    result4= pthread_create(&thread_candy, NULL, prep_candy, NULL);
    if(result4==-1)
    {
      printf("Error in creating the thread of candy\n");
      exit(1);
    }
  }
  else {
    printf("Error in genrating the random number\n");
  }

}

int main()
{
  pthread_t thread_order;
  while(1)
  {
  int result1=pthread_create(&thread_order, NULL, take_order ,NULL );
  if(result1==-1)
  {
    printf("Error in creating the order taking thread\n");
    exit(1);
  }
  }
  pthread_join(thread_order, NULL);
  return 0;
}
