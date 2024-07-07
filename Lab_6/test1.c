#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define MESSAGE_SIZE 100 // Define the maximum size of the message

int main() {
    key_t key = IPC_CREAT | 1234; // Unique key for shared memory segment
    int shmid; // Shared memory identifier
    char *message = "Hello from shared memory!"; // Message to write
    
    // Create the shared memory segment
    shmid = shmget(key, MESSAGE_SIZE + 1, IPC_CREAT | 0666); // Permissions: read & write
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    
    // Attach to the shared memory segment
    char *shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    // Copy the message to shared memory
    strncpy(shared_memory, message, MESSAGE_SIZE); // Safe copy, avoids buffer overflow
    
    // Detach from the shared memory segment
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(1);
    }
    
    printf("Message written to shared memory: %s\n", message);

    return 0;
}
