#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>
int main ()
{
  key_t key= 1234;
  int i=0;
  int shmid;
  shmid = shmget(key, sizeof(int), IPC_CREAT|0666);
  if(shmid<0)
  {
    perror("shmget");
    exit(1);
  }
  
// Attach the shared memory segment to the address space of the process
    int *shared_memory = (int *)shmat(shmid, NULL, 0);
    if (shared_memory == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    i = i+1; // Example integer value

    // Write the integer value directly into shared memory
    *shared_memory = i;
  // Detach from the shared memory segment
  if (shmdt(shared_memory) == -1) {
    perror("shmdt");
    exit(1);
  }
  printf("Value written to shared memory: %d\n", i);
  return 0;
}
