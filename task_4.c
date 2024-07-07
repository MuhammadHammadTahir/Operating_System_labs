#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct sum {
  int lower_limit;
  int upper_limit;
  int *result;
};

void *calculate(void *args)
{
  struct sum *half = (struct sum *)args;
  int local_sum=0;
  for(int i=half->lower_limit; i <= half->upper_limit; i++)
  {
    local_sum = local_sum+i;
  }

  *(half->result)=local_sum;
  return NULL;
}

int main()
{
  int upper_limit, mid;
  int result1, result2, final_result;

  printf("Enter the Upper_limit : ");
  scanf("%d", &upper_limit);
  mid=upper_limit/2;

  struct sum s1,s2;
  s1.lower_limit=1;
  s1.upper_limit=mid;
  s1.result=&result1;

  s2.lower_limit=mid+1;
  s2.upper_limit=upper_limit;
  s2.result=&result2;

  pthread_t thread1, thread2;
  int status;

  status= pthread_create(&thread1, NULL, calculate, &s1);
  if(status==-1)
  {
    printf("Error in creating the thread1\n");
    exit(1);
  }

  status= pthread_create(&thread2, NULL, calculate, &s2);
  if(status==-1)
  {
    printf("Error in creating thread2\n");
    exit(1);
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2 ,NULL);
  
  //here the * is to dereference it bcz the s1.result is the the pointer to the variable that store the result1 so to get the 
  // actual value we have to dereference it.

  final_result= *(s1.result) + *(s2.result);  
  printf("Sum of the natural numbers upto %d = %d\n", upper_limit, final_result);
  return 0;
}
