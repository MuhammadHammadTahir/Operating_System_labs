#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
  key_t key =1234;
  int shmid;
  shmid= shmget(key, sizeof(int), 0);
  int *shared_memory;
  if (shmid < 0) {
    perror("shmget");
    exit(1);
  }
  // Attach to the shared memory segment  
  shared_memory = (int *)shmat(shmid, NULL, 0);

  if (shared_memory == (int *)-1) {
        perror("shmat");
        exit(1);
    }
  int value=*shared_memory;
  printf("The incremented value is %d\n",value);
  return 0;
}
