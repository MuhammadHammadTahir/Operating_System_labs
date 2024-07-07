#include <stdio.h>

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

void completion_of_process(struct process* pro, int curr_time) {
  pro->completion_time = pro->burst_time + curr_time;
}

void waiting_time_of_the_process(struct process* pro) {
  pro->waiting_time = pro->turnaround_time - pro->burst_time;
}

void turnaround_time_of_the_process(struct process* pro) {
  pro->turnaround_time = pro->completion_time - pro->arrival_time;
}

void fcfs(struct process* processes, int n)
{
  float avg_waiting, avg_turn;
  int rear=-1, front=0, current_time=0 ,sum_wait=0, sum_turn=0; 
  struct process ready_queue[100];
  for(int i=0; i<n; i++)
  {
    rear++;
    ready_queue[rear]=processes[i];
  }

  while(front<= rear)
  {
    struct process p= ready_queue[front];
    front++;

    if (current_time < p.arrival_time) {
            current_time = p.arrival_time;  
    }
    completion_of_process(&p, current_time);
    current_time=p.completion_time;
    turnaround_time_of_the_process(&p);
    waiting_time_of_the_process(&p);
    printf("Completion time of %d process is %d\n",p.pid ,p.completion_time);
    printf("Turnaround time of %d process is %d\n",p.pid ,p.turnaround_time);
    printf("waiting    time of %d process is %d\n",p.pid ,p.waiting_time);

    sum_wait+=p.waiting_time;
    sum_turn+=p.turnaround_time;
  }

  avg_waiting=(float)sum_wait/n;
  avg_turn= (float)sum_turn/n;

  printf("Average waiting time = %f\n", avg_waiting);
  printf("Average turnaround time =%f\n", avg_turn);
}

void SJF(struct process* processes, int n) {
  float avg_waiting = 0, avg_turn = 0;
  int current_time = 0, sum_wait = 0, sum_turn = 0, completed = 0;
  
  while (completed < n) {
    int shortest = -1;
    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
        if (shortest == -1 || processes[i].burst_time < processes[shortest].burst_time)
          shortest = i;
      }
    }
    if (shortest == -1) {
      current_time++;
      continue;
    }
    struct process *p = &processes[shortest];
    completion_of_process(p, current_time);
    current_time = p->completion_time;
    turnaround_time_of_the_process(p);
    waiting_time_of_the_process(p);
    printf("Completion time of %d process is %d\n", p->pid, p->completion_time);
    printf("Turnaround time of %d process is %d\n", p->pid, p->turnaround_time);
    printf("Waiting time of %d process is %d\n", p->pid, p->waiting_time);
    sum_wait += p->waiting_time;
    sum_turn += p->turnaround_time;
    completed++;
  }

  avg_waiting = (float)sum_wait / n;
  avg_turn = (float)sum_turn / n;

  printf("Average waiting time = %f\n", avg_waiting);
  printf("Average turnaround time = %f\n", avg_turn);
}


void PriorityScheduling(struct process* processes, int n) {
  float avg_waiting = 0, avg_turn = 0;
  int current_time = 0, sum_wait = 0, sum_turn = 0, completed = 0;
  
  while (completed < n) {
    int highest_priority = -1;
    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
        if (highest_priority == -1 || processes[i].priority < processes[highest_priority].priority)
          highest_priority = i;
      }
    }
    if (highest_priority == -1) {
      current_time++;
      continue;
    }
    struct process *p = &processes[highest_priority];
    p->completion_time = current_time + p->burst_time; // Update completion time directly in the processes array
    current_time = p->completion_time;
    turnaround_time_of_the_process(p);
    waiting_time_of_the_process(p);
    printf("Completion time of %d process is %d\n", p->pid, p->completion_time);
    printf("Turnaround time of %d process is %d\n", p->pid, p->turnaround_time);
    printf("Waiting time of %d process is %d\n", p->pid, p->waiting_time);
    sum_wait += p->waiting_time;
    sum_turn += p->turnaround_time;
    completed++;
  }

  avg_waiting = (float)sum_wait / n;
  avg_turn = (float)sum_turn / n;

  printf("Average waiting time = %f\n", avg_waiting);
  printf("Average turnaround time = %f\n", avg_turn);
}

void RoundRobin(struct process* processes, int n, int time_quantum) {
  float avg_waiting = 0, avg_turn = 0;
  int current_time = 0, sum_wait = 0, sum_turn = 0, completed = 0;
  
  while (completed < n) {
    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
        int remaining_burst = processes[i].burst_time - processes[i].remaining_time;
        int execute_time = remaining_burst < time_quantum ? remaining_burst : time_quantum;
        processes[i].remaining_time -= execute_time;
        current_time += execute_time;
        if (processes[i].remaining_time == 0) {
          completion_of_process(&processes[i], current_time);
          turnaround_time_of_the_process(&processes[i]);
          waiting_time_of_the_process(&processes[i]);
          printf("Completion time of %d process is %d\n", processes[i].pid, processes[i].completion_time);
          printf("Turnaround time of %d process is %d\n", processes[i].pid, processes[i].turnaround_time);
          printf("Waiting time of %d process is %d\n", processes[i].pid, processes[i].waiting_time);
          sum_wait += processes[i].waiting_time;
          sum_turn += processes[i].turnaround_time;
          completed++;
        }
      }
    }
  }

  avg_waiting = (float)sum_wait / n;
  avg_turn = (float)sum_turn / n;

  printf("Average waiting time = %f\n", avg_waiting);
  printf("Average turnaround time = %f\n", avg_turn);
}

int main() {
  struct process processes[] = {
    {1,0,3,0,0,0,2}, // Priority Scheduling: priority = 2
    {2,1,4,0,0,0,1}, // Priority Scheduling: priority = 1
    {3,2,6,0,0,0,3}, // Priority Scheduling: priority = 3
    {4,3,2,0,0,0,4}, // Priority Scheduling: priority = 4
    {5,4,7,0,0,0,5}  // Priority Scheduling: priority = 5
  };

  int n = sizeof(processes)/sizeof(processes[0]);
  int time_quantum = 2; // Round Robin time quantum

  printf("First Come First Serve:\n");
  fcfs(processes, n);

  printf("\nShortest Job First:\n");
  SJF(processes, n);

  printf("\nPriority Scheduling:\n");
  PriorityScheduling(processes, n);

  printf("\nRound Robin:\n");
  RoundRobin(processes, n, time_quantum);

  return 0;
}
