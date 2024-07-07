#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define MESSAGE_SIZE 100 // Define the maximum size of the message
int main() {
key_t key = 1234; // Same key used in write_to_shared_memory.c
int shmid; // Shared memory identifier
char *shared_memory; // Pointer to shared memory segment
// Get the shared memory segment identifier (already created by program 1)
shmid = shmget(key, 0, 0); // No need for size or creation flags
if (shmid < 0) {
perror("shmget");
exit(1);
}
// Attach to the shared memory segment
shared_memory = shmat(shmid, NULL, 0);

if (shared_memory == (char *) -1) {
perror("shmat");
exit(1);
}
// Read the message from shared memory
char message[MESSAGE_SIZE + 1]; // Allocate space to store the message
strncpy(message, shared_memory, MESSAGE_SIZE); // Safe copy
message[MESSAGE_SIZE] = '\0'; // Ensure null termination (optional)
// Detach from the shared memory segment
if (shmdt(shared_memory) == -1) {
perror("shmdt");
exit(1);
}
printf("Message read from shared memory: %s\n", message);
return 0;
}
