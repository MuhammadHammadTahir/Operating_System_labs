#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int maxi;
int mini;
float avg=0.0;

int size=0;

void *average_fun(void *args)
{
  int *arr = (int *)args;
  int sum=0;
  for(int i=0;i<size;i++)
  {
    sum= sum + arr[i];
  }
  avg = sum/(float)size;
  return NULL;
}

void *max_fun(void *args)
{
  int *arr = (int *)args;
  int max=arr[0];
  for(int i=0;i<size;i++)
  {
    if(max < arr[i])
    {
      max = arr[i];
    }
  }
  maxi =max;

  return NULL;
}

void *min_fun(void *args)
{
  int *arr = (int *)args;
  int min=arr[0];
  for(int i=0;i<size;i++)
  {
    if(min>arr[i])
    {
      min = arr[i];
    }
  }
  mini =min;

  return NULL;
}


int main()
{
  int arry[100];
  char ch;
  for(int i=0; i<100; i++)
  {
    printf("\nEnter the Interger Number : ");
    scanf("%d", &arry[i]);
    size++;
    printf("Do you want to add another number ? Y/N  : ");
    scanf(" %c", &ch);
    if(ch=='N' || ch =='n')
    {
      break;
    }
      else if (ch=='Y' || ch=='y') {
      continue;
      }
    else{
      printf("Wrong input\n");
      exit(1);
    }
  }
  
  pthread_t thread[2];
  pthread_create(&thread[0], NULL, average_fun, arry);
  pthread_create(&thread[1], NULL, min_fun, arry);
  pthread_create(&thread[2], NULL, max_fun, arry);

  for(int i=0; i<3; i++)
  {
    pthread_join(thread[i], NULL);
  }

  printf("The average value is %f\n", avg);
  printf("The maximum value is %d\n", maxi);
  printf("The minimum value is %d\n", mini);

  return 0;
}
