#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *serve(void *args)
{
  int *ch = (int *) args;
  if(*ch==1)
  {
    sleep(20);
    printf("Biryani is served\n");
  }
  else if(*ch==2)
  {
    sleep(20);
    printf("Pasta is serverd\n");
  }
  else if (*ch==3) {
    sleep(20);
    printf("Pizza is served\n");
  }
  else if (*ch==4) {
    sleep(20);
    printf("Soda is serverd\n");
  }
  else if (*ch==5) {
    sleep(20);
    printf("Coffee is serverd\n");
  }
  else if (*ch==6) {
    sleep(20);
    printf("Milkshake is serverd\n");
  }
  else if (*ch==7) {
    printf("No Order\n");
  }
  return NULL;
}


void *menu(void *args)
{
  int ch, result;
  pthread_t thread[6];
  while (1) {
  printf("Select from the Menu:\n1) Biryani\n2) Pasta\n3) Pizza\n4) Soda\n5) Coffee\n6) Milkshake\n7) Finish Order\n");
  scanf("%d", &ch);
  if(ch<1 || ch>7)
    {
      printf("Invalid input\n");
      continue;
    }
    else {
      pthread_create(&thread[ch-1] , NULL, serve, &ch);
    }
    if(ch==7)
    {
      pthread_join(thread[6], NULL);
      break;
    }
  }

  return NULL;
}



int main()
{
  pthread_t thread_1;
  int result;

  result=pthread_create(&thread_1, NULL, menu, NULL);
  if(result==-1)
  {
    printf("Error in creating the thread_1\n");
    exit(1);
  }
  pthread_join(thread_1, NULL);
  return 0;
}
