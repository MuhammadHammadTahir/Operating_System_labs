#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

bool visited[MAX_PROCESSES];

void input(int processes, int resources) {
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool is_safe_sequence(int processes, int resources, int *safe_sequence) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    // Initialize work with available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int r = 0; r < resources; r++) {
                    if (need[p][r] > work[r]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int r = 0; r < resources; r++) {
                        work[r] += allocation[p][r];
                    }
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // No safe sequence found
        }
    }
    return true;
}

bool check_deadlock(int processes, int resources) {
    int safe_sequence[MAX_PROCESSES];
    return !is_safe_sequence(processes, resources, safe_sequence);
}

void print_safe_sequence(int *safe_sequence, int processes) {
    printf("Safe sequence is: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
}

int main() {
    int processes, resources;
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    input(processes, resources);

    int choice;
    while (1) {
        printf("\n1. Request Resources\n2. Release Resources\n3. Check for Deadlock\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int pid, req[MAX_RESOURCES];
            printf("Enter process ID and requested resources:\n");
            scanf("%d", &pid);
            for (int i = 0; i < resources; i++) {
                scanf("%d", &req[i]);
            }

            bool can_allocate = true;
            for (int i = 0; i < resources; i++) {
                if (req[i] > need[pid][i] || req[i] > available[i]) {
                    can_allocate = false;
                    break;
                }
            }

            if (can_allocate) {
                for (int i = 0; i < resources; i++) {
                    available[i] -= req[i];
                    allocation[pid][i] += req[i];
                    need[pid][i] -= req[i];
                }
                printf("Resources allocated successfully.\n");
            } else {
                printf("Resources cannot be allocated.\n");
            }

        } else if (choice == 2) {
            bool can_allocate=true;
            int pid, rel[MAX_RESOURCES];
            printf("Enter process ID and released resources:\n");
            scanf("%d", &pid);
            for (int i = 0; i < resources; i++) {
                scanf("%d", &rel[i]);
            }

            for (int i = 0; i < resources; i++) {
                if (rel[i] > allocation[pid][i]) {
                    printf("Cannot release more resources than allocated.\n");
                    can_allocate = false;
                    break;
                }
            }

            for (int i = 0; i < resources; i++) {
                available[i] += rel[i];
                allocation[pid][i] -= rel[i];
                need[pid][i] += rel[i];
            }
            printf("Resources released successfully.\n");

        } else if (choice == 3) {
            bool can_allocate=true;
            if (check_deadlock(processes, resources)) {
                printf("Deadlock detected!\n");
            } else {
                int safe_sequence[MAX_PROCESSES];
                if (is_safe_sequence(processes, resources, safe_sequence)) {
                    print_safe_sequence(safe_sequence, processes);
                }
            }
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
