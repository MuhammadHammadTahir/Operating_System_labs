#include <stdio.h>
#include <string.h>

// Function to copy the block size array
void copyArray(int dest[], int src[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (blockSize[i] >= processSize[j]) {
                allocation[j] = i;
                blockSize[i] -= processSize[j];
                printf("Process %d allocated block %d (First Fit)\n", j + 1, i + 1);
                break;
            }
        }
        if (allocation[j] == -1) {
            printf("Process %d not allocated (First Fit)\n", j + 1);
        }
    }
}

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int next_block = 0;
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int j = 0; j < n; j++) {
        int found = 0;
        for (int i = next_block; i < m; i++) {
            if (blockSize[i] >= processSize[j]) {
                allocation[j] = i;
                blockSize[i] -= processSize[j];
                next_block = (i + 1) % m;
                found = 1;
                printf("Process %d allocated block %d (Next Fit)\n", j + 1, i + 1);
                break;
            }
        }
        if (!found) {
            for (int i = 0; i < next_block; i++) {
                if (blockSize[i] >= processSize[j]) {
                    allocation[j] = i;
                    blockSize[i] -= processSize[j];
                    next_block = (i + 1) % m;
                    found = 1;
                    printf("Process %d allocated block %d (Next Fit)\n", j + 1, i + 1);
                    break;
                }
            }
        }
        if (!found) {
            printf("Process %d not allocated (Next Fit)\n", j + 1);
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int worst_idx = -1;
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (blockSize[i] >= processSize[j]) {
                if (worst_idx == -1 || blockSize[i] > blockSize[worst_idx]) {
                    worst_idx = i;
                }
            }
        }
        if (worst_idx != -1) {
            int i = worst_idx;
            allocation[j] = worst_idx;
            blockSize[i] -= processSize[j];
            printf("Process %d allocated block %d (Worst Fit)\n", j + 1, worst_idx + 1);
            worst_idx = -1; // Reset for next process
        } else {
            printf("Process %d not allocated (Worst Fit)\n", j + 1);
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int best_idx = -1;
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (blockSize[i] >= processSize[j]) {
                if (best_idx == -1 || blockSize[i] - processSize[j] < blockSize[best_idx] - processSize[j]) {
                    best_idx = i;
                }
            }
        }
        if (best_idx != -1) {
            allocation[j] = best_idx;
            blockSize[best_idx] -= processSize[j];
            printf("Process %d allocated block %d (Best Fit)\n", j + 1, best_idx + 1);
            best_idx = -1; // Reset for next process
        } else {
            printf("Process %d not allocated (Best Fit)\n", j + 1);
        }
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    int blockSizeCopy[m];

    // First Fit
    copyArray(blockSizeCopy, blockSize, m);
    firstFit(blockSizeCopy, m, processSize, n);

    // Next Fit
    copyArray(blockSizeCopy, blockSize, m);
    nextFit(blockSizeCopy, m, processSize, n);

    // Worst Fit
    copyArray(blockSizeCopy, blockSize, m);
    worstFit(blockSizeCopy, m, processSize, n);

    // Best Fit
    copyArray(blockSizeCopy, blockSize, m);
    bestFit(blockSizeCopy, m, processSize, n);

    return 0;
}
