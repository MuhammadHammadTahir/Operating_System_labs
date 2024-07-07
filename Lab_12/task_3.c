#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_NAME "/shm_balance"
#define SEM_NAME "/sem_balance"

int main() {
    // Shared memory for the bank balance
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    int *balance = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (balance == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    *balance = 0;  // Initial balance

    // Semaphore for synchronizing access to the balance
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        // Child process 1 (Depositor)
        for (int i = 0; i < 5; i++) {
            sem_wait(sem);
            printf("Depositor: Adding 100\n");
            *balance += 100;
            printf("Balance after deposit: %d\n", *balance);
            sem_post(sem);
            sleep(1);
        }
        exit(0);
    } else if (pid1 > 0) {
        pid2 = fork();
        if (pid2 == 0) {
            // Child process 2 (Withdrawer)
            for (int i = 0; i < 5; i++) {
                sem_wait(sem);
                if (*balance >= 50) {
                    printf("Withdrawer: Removing 50\n");
                    *balance -= 50;
                    printf("Balance after withdrawal: %d\n", *balance);
                } else {
                    printf("Withdrawer: Insufficient funds\n");
                }
                sem_post(sem);
                sleep(1);
            }
            exit(0);
        } else if (pid2 > 0) {
            // Parent process
            wait(NULL);
            wait(NULL);

            printf("Final balance: %d\n", *balance);

            // Clean up
            if (munmap(balance, sizeof(int)) == -1) {
                perror("munmap");
                exit(1);
            }

            if (shm_unlink(SHM_NAME) == -1) {
                perror("shm_unlink");
                exit(1);
            }

            if (sem_close(sem) == -1) {
                perror("sem_close");
                exit(1);
            }

            if (sem_unlink(SEM_NAME) == -1) {
                perror("sem_unlink");
                exit(1);
            }
        } else {
            perror("fork");
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
