#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

typedef struct {
    int size;
    int original_size;
    int allocated;
    int start_address;
} Block;

typedef struct {
    int size;
    int allocated_block;
} Process;

void first_fit(Block blocks[], int block_count, Process processes[], int process_count) {
    for (int i = 0; i < process_count; i++) {
        processes[i].allocated_block = -1;
        for (int j = 0; j < block_count; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                processes[i].allocated_block = j;
                blocks[j].allocated = 1;
        if(j==0){
          blocks[j].start_address = 0;

        }
        else{
                blocks[j].start_address = blocks[j-1].original_size + 1;
        }
                blocks[j].size -= processes[i].size; // Update block size to reflect allocation
                break;
            }
        }
    }
}

void print_allocation(Process processes[], int process_count, Block blocks[]) {
    printf("\nProcess Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\tBlock Start Address\n");

    for (int i = 0; i < process_count; i++) {
        if (processes[i].allocated_block != -1) {
            int block_no = processes[i].allocated_block;
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].size, block_no + 1, blocks[block_no].start_address);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, processes[i].size);
        }
    }
}

void calculate_fragmentation(Block blocks[], int block_count) {
    int internal_fragmentation = 0;
    int external_fragmentation = 0;

    for (int i = 0; i < block_count; i++) {
        if (blocks[i].allocated) {
            internal_fragmentation += blocks[i].size;
        } else {
            external_fragmentation += blocks[i].size;
        }
    }

    printf("\nTotal Internal Fragmentation: %d\n", internal_fragmentation);
    printf("Total External Fragmentation: %d\n", external_fragmentation);
}

int main() {
    int block_count, process_count;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &block_count);
    Block blocks[MAX_BLOCKS];
    
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < block_count; i++) {
        scanf("%d", &blocks[i].size);
        blocks[i].original_size = blocks[i].size;
        blocks[i].allocated = 0;
        blocks[i].start_address = 0;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &process_count);
    Process processes[MAX_PROCESSES];

    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < process_count; i++) {
        scanf("%d", &processes[i].size);
        processes[i].allocated_block = -1;
    }

    first_fit(blocks, block_count, processes, process_count);
    print_allocation(processes, process_count, blocks);
    calculate_fragmentation(blocks, block_count);

    return 0;
}
