#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int arr[100];

void *fabonachi(void *argu)
{
  int *range= (int *) argu;
  int first = 0;
  int second = 1;
  arr[0]=0;
  arr[1]=1;
  int final;
  for(int i=2; i < *(range); i++)
  {
    final=first+second;
    first=second;
    second=final;
    arr[i]=final;
  }
  return NULL;
}

int main()
{
  int range;
  printf("Enter the number of fabonachi series you want : ");
  scanf("%d", &range);

  pthread_t thread_child;
  int result;
  result = pthread_create(&thread_child,  NULL , fabonachi, &range);
  if(result == -1)
  {
    printf("Error in creating the child thread \n");
    exit(1);
  }

  pthread_join(thread_child, NULL);
  printf("Resulting series = ");
  for(int i=0; i<range; i++)
  {
    if(i==range-1)
    {
      printf("%d ", arr[i]);
      break;
    }
    printf("%d, ", arr[i]);
  }


  return 0;
}
