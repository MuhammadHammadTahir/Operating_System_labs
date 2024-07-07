#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void deposite(int shm_id)
{
  int depo;
  printf("Enter the amount to be deposite : ");
  scanf("%d",&depo);
  if(depo>=0)
  {
  int *curr= (int*) shmat(shm_id, NULL, 0);
  if(curr== (int*)-1)
  {
    perror("shmat");
    exit(1);
  }
  *curr+=depo;
  printf("Amount Deposited\n");
  }
  else {
    printf("You entered the wrong amount\n");
  }
}

void withdraw(int shm_id)
{
  int with;
  printf("Enter the amount to be withdraw : ");
  scanf("%d",&with);
  int *curr= (int*) shmat(shm_id, NULL, 0);
  if(curr== (int*)-1)
  {
    perror("shmat");
    exit(1);
  }
  if (with>*curr)
  {
    printf("!!!Not enough balance!!!!\n");
  }
  else {
    *curr-=with;
    printf("Amount withdrawed\n");
  }
}


int main()
{
  key_t key=IPC_CREAT|1234;
  int shm_id;
  shm_id=shmget(key, sizeof(int), IPC_CREAT|0666);
  if(shm_id==-1)
  {
    perror("shmget");
    exit(1);
  }
  int *balance = (int*)shmat(shm_id, NULL, 0);
  if(balance==(int*)-1)
  {
    perror("shmat");
    exit(1);
  }
  *balance =100; //initial balance
  pid_t pid1, pid2;

  pid1=fork();
  if(pid1 < 0)
  {
    printf("Error in creating the child process 1\n");
    exit(1);
  }
  if(pid1==0)
  {
    deposite(shm_id);
    exit(0);
  }
  else {
    wait(NULL);
    printf("Balance after deposite = %d\n", *balance);
  }
  if(pid1>0)
  {
    pid2=fork();
    if(pid2<0)
    {
      printf("Error in creating the process 2\n");
      exit(1);
    }
    if(pid2==0)
    {
      withdraw(shm_id);
      exit(0);
    }
    else{
      wait(NULL);
      printf("Balance after withdraw = %d\n", *balance);
    }
  }



}
