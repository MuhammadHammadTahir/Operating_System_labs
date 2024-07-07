#include <stdio.h>

// Process struct definition
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int priority; // For Priority Scheduling
    int remaining_time; // For Round Robin
};

// Function to execute a process
void execute(struct process *p, int time) {
    if (p->remaining_time <= time) {
        p->completion_time += p->remaining_time;
        p->remaining_time = 0;
    } else {
        p->remaining_time -= time;
        p->completion_time += time;
    }
}

// Function to check for new arrivals with higher priority
int new_higher_priority_exists(struct process *ready_queue, int n, struct process *current_process) {
    for (int i = 0; i < n; i++) {
        if (ready_queue[i].arrival_time <= current_process->completion_time &&
            ready_queue[i].priority < current_process->priority &&
            ready_queue[i].remaining_time > 0) {
            return 1;
        }
    }
    return 0;
}

// Function to select process with highest priority
int select_highest_priority(struct process *ready_queue, int n) {
    int highest_priority = 0;
    for (int i = 1; i < n; i++) {
        if (ready_queue[i].priority < ready_queue[highest_priority].priority &&
            ready_queue[i].remaining_time > 0) {
            highest_priority = i;
        }
    }
    return highest_priority;
}

// Function to enqueue a process
void enqueue(struct process *queue, int n, struct process p) {
    for (int i = 0; i < n; i++) {
        if (queue[i].pid == -1) {
            queue[i] = p;
            return;
        }
    }
}

// Function to dequeue a process
void dequeue(struct process *queue, int n, struct process *p) {
    for (int i = 0; i < n - 1; i++) {
        queue[i] = queue[i + 1];
    }
    queue[n - 1].pid = -1;
}

// Priority Scheduling algorithm
void PriorityScheduling(struct process *processes, int n) {
    struct process ready_queue[n];
    for (int i = 0; i < n; i++) {
        enqueue(ready_queue, n, processes[i]);
    }
    int current_time = 0;
    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (ready_queue[i].arrival_time <= current_time && ready_queue[i].remaining_time > 0) {
                found = 1;
                break;
            }
        }
        if (!found)
            break;
        int highest_priority = select_highest_priority(ready_queue, n);
        while (ready_queue[highest_priority].remaining_time > 0) {
            execute(&ready_queue[highest_priority], 1);
            current_time++;
            if (new_higher_priority_exists(ready_queue, n, &ready_queue[highest_priority])) {
                enqueue(ready_queue, n, ready_queue[highest_priority]);
                dequeue(ready_queue, n, &ready_queue[highest_priority]);
                highest_priority = select_highest_priority(ready_queue, n);
            }
        }
        ready_queue[highest_priority].completion_time = current_time;
        dequeue(ready_queue, n, &ready_queue[highest_priority]);
    }
    // Calculate waiting and turnaround times for all processes
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("Average Waiting Time for Priority Scheduling: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time for Priority Scheduling: %.2f\n", total_turnaround_time / n);
}

// Round Robin algorithm
void RoundRobin(struct process *processes, int n, int time_quantum) {
    struct process ready_queue[n];
    for (int i = 0; i < n; i++) {
        enqueue(ready_queue, n, processes[i]);
    }
    int current_time = 0;
    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (ready_queue[i].arrival_time <= current_time && ready_queue[i].remaining_time > 0) {
                found = 1;
                break;
            }
        }
        if (!found)
            break;
        struct process current_process = ready_queue[0];
        dequeue(ready_queue, n, &current_process);
        execute(&current_process, time_quantum);
        current_time += time_quantum;
        if (current_process.remaining_time > 0) {
            enqueue(ready_queue, n, current_process);
        } else {
            current_process.completion_time = current_time;
        }
    }
    // Calculate waiting and turnaround times for all processes
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("Average Waiting Time for Round Robin: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time for Round Robin: %.2f\n", total_turnaround_time / n);
}

// Function to print the result
void printResult(struct process *processes, int n) {
    printf("PID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].completion_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    struct process processes[] = {
        {1,0,3,0,0,0,2}, // Priority Scheduling: priority = 2
        {2,1,4,0,0,0,1}, // Priority Scheduling: priority = 1
        {3,2,6,0,0,0,3}, // Priority Scheduling: priority = 3
        {4,3,2,0,0,0,4}, // Priority Scheduling: priority = 4
        {5,4,7,0,0,0,5}  // Priority Scheduling: priority = 5
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    printf("Priority Scheduling:\n");
    PriorityScheduling(processes, n);
    printResult(processes, n);

    struct process processes2[] = {
        {1,0,3,0,0,0,0,3}, // Round Robin: time_quantum = 3
        {2,1,4,0,0,0,0,1}, // Round Robin: time_quantum = 3
        {3,2,6,0,0,0,0,4}, // Round Robin: time_quantum = 3
        {4,3,2,0,0,0,0,2}  // Round Robin: time_quantum = 3
    };
    n = sizeof(processes2) / sizeof(processes2[0]);
    printf("\nRound Robin:\n");
    RoundRobin(processes2, n, 3);
    printResult(processes2, n);

    return 0;
}
