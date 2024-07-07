#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PRINTERS 3
#define NUM_PROCESSES 10

typedef struct {
    int priority;
    int printer_assigned;
} Process;

Process processes[NUM_PROCESSES];
int printer_available[NUM_PRINTERS] = {1, 1, 1}; // 1 for available, 0 for busy

pthread_mutex_t mutex;
pthread_cond_t printer_available_cv;

void *process_thread(void *arg) {
    Process *process = (Process *)arg;
    
    pthread_mutex_lock(&mutex);
    while (1) {
        int allocated = 0;
        for (int i = 0; i < NUM_PRINTERS; i++) {
            if (printer_available[i]) {
                printer_available[i] = 0;
                process->printer_assigned = i;
                allocated = 1;
                break;
            }
        }
        
        if (allocated) {
            printf("Process with priority %d allocated Printer %d\n", process->priority, process->printer_assigned + 1);
            pthread_mutex_unlock(&mutex);
            sleep(2); // Simulating printing time
            pthread_mutex_lock(&mutex);
            printer_available[process->printer_assigned] = 1;
            printf("Process with priority %d released Printer %d\n", process->priority, process->printer_assigned + 1);
            pthread_cond_broadcast(&printer_available_cv);
            break;
        } else {
            pthread_cond_wait(&printer_available_cv, &mutex);
        }
    }
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

void create_process_threads() {
    pthread_t threads[NUM_PROCESSES];
    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].priority = rand() % 10; // Random priority
        processes[i].printer_assigned = -1;
        pthread_create(&threads[i], NULL, process_thread, (void *)&processes[i]);
    }
    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&printer_available_cv, NULL);
    
    create_process_threads();
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&printer_available_cv);
    
    return 0;
}
