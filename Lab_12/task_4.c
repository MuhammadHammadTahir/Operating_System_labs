#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

void calculate_waiting_and_turnaround_times(Process *processes, int n, int time_quantum) {
    int current_time = 0;
    int completed = 0;
    bool done = false;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        done = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                done = false;
                printf(" P%d (%d) |", processes[i].pid, current_time);

                if (processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        if (done) {
            current_time++;
        }
    }
    printf("\n");
}

void print_avg_times(Process *processes, int n) {
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].arrival_time = rand() % 10;
        processes[i].burst_time = (rand() % 10) + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    printf("\nProcesses:\n");
    printf("PID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time);
    }

    printf("\nEnter the time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nSimulating Round Robin Scheduling...\n");
    calculate_waiting_and_turnaround_times(processes, n, time_quantum);
    print_avg_times(processes, n);

    return 0;
}
