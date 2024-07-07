#include <stdio.h>
#define PAGE_SIZE 1024 // 1 KB
#define MAIN_MEMORY_SIZE 4096 // 4 KB

int main() {
    // Define process sizes
    int process_sizes[] = {4096, 1228, 3840}; // Sizes in bytes, ensuring Process 1 is large enough

    // Calculate number of page frames per process
    int num_page_frames[3];
    for (int i = 0; i < 3; i++) {
        num_page_frames[i] = (process_sizes[i] + PAGE_SIZE - 1) / PAGE_SIZE;
    }

    // Define page tables (assuming 4 frames in main memory)
    int page_table[3][4];

    // Initialize page tables (assuming no initial frame allocation)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            page_table[i][j] = -1; // -1 indicates frame not assigned
        }
    }

    // Available memory (frame numbers)
    int available_frames[4] = {0, 1, 2, 3};

    // Simulate frame allocation using first fit
    for (int i = 0; i < 3; i++) {
        int frames_allocated = 0;
        for (int j = 0; j < 4 && frames_allocated < num_page_frames[i]; j++) {
            if (available_frames[j] != -1) {
                page_table[i][frames_allocated] = available_frames[j];
                available_frames[j] = -1;
                frames_allocated++;
            }
        }
        if (frames_allocated < num_page_frames[i]) {
            printf("Not enough memory to allocate frames for process %d\n", i + 1);
        }
    }

    // Print page tables
    printf("Page Tables:\n");
    for (int i = 0; i < 3; i++) {
        printf("Process %d: ", i + 1);
        for (int j = 0; j < 4; j++) {
            printf("%d ", page_table[i][j]);
        }
        printf("\n");
    }

    // Calculate physical address for logical address 3072 of process 1
    int logical_address = 3072;
    int process_id = 0; // Assuming process 1 (modify for other processes)
    int page_offset = logical_address % PAGE_SIZE;
    printf("My name is Muhammad Hammad Tahir and my roll# is 033\n");
    int page_number = logical_address / PAGE_SIZE;

    if (page_number >= num_page_frames[process_id]) {
        printf("Invalid logical address (exceeds process size)\n");
    } else if (page_table[process_id][page_number] == -1) {
        printf("Invalid logical address (page not in memory)\n");
    } else {
    printf("%d\n",page_table[process_id][page_number]);
        int physical_address = (page_table[process_id][page_number] * PAGE_SIZE) + page_offset;
        printf("Physical address for logical address %d of process 1: %d\n", logical_address, physical_address);
    }

    return 0;
}
