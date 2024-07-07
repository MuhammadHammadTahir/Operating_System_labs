#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_RANGE 9
#define PAGE_REFERENCE_LENGTH 20

// Function to simulate FIFO page replacement algorithm
int FIFO(int page_references[], int num_frames) {
    int page_table[num_frames];
    int queue[num_frames];
    int front = 0, rear = 0;
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        page_table[i] = -1;
    }

    for (int i = 0; i < PAGE_REFERENCE_LENGTH; i++) {
        int page = page_references[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (page_table[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (rear - front < num_frames) {
                page_table[rear % num_frames] = page;
                queue[rear % num_frames] = page;
                rear++;
            } else {
                int page_to_replace = queue[front % num_frames];
                for (int j = 0; j < num_frames; j++) {
                    if (page_table[j] == page_to_replace) {
                        page_table[j] = page;
                        break;
                    }
                }
                queue[front % num_frames] = page;
                front++;
                rear++;
                page_faults++;
            }
        }
    }
    return page_faults;
}

// Node structure for the doubly linked list used in LRU
typedef struct Node {
    int page;
    struct Node* prev;
    struct Node* next;
} Node;

// Doubly linked list structure for LRU
typedef struct {
    Node* head;
    Node* tail;
} DoublyLinkedList;

void move_to_head(DoublyLinkedList* list, Node* node) {
    if (list->head == node) return;
    if (node == list->tail) {
        list->tail = node->prev;
        list->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    node->prev = NULL;
}

void append(DoublyLinkedList* list, Node* node) {
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

Node* pop_tail(DoublyLinkedList* list) {
    if (list->tail == NULL) return NULL;
    Node* node = list->tail;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    return node;
}

// Function to simulate LRU page replacement algorithm
int LRU(int page_references[], int num_frames) {
    DoublyLinkedList list = {NULL, NULL};
    int page_table[num_frames];
    Node* node_map[PAGE_RANGE];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        page_table[i] = -1;
    }
    for (int i = 0; i < PAGE_RANGE; i++) {
        node_map[i] = NULL;
    }

    for (int i = 0; i < PAGE_REFERENCE_LENGTH; i++) {
        int page = page_references[i];
        if (node_map[page] != NULL) {
            move_to_head(&list, node_map[page]);
            continue;
        }

        if (list.head == NULL || list.tail - list.head < num_frames) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->page = page;
            new_node->prev = new_node->next = NULL;
            append(&list, new_node);
            node_map[page] = new_node;
        } else {
            Node* least_recently_used = pop_tail(&list);
            int page_to_replace = least_recently_used->page;
            for (int j = 0; j < num_frames; j++) {
                if (page_table[j] == page_to_replace) {
                    page_table[j] = page;
                    break;
                }
            }
            free(least_recently_used);
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->page = page;
            new_node->prev = new_node->next = NULL;
            append(&list, new_node);
            node_map[page] = new_node;
            page_faults++;
        }
    }
    return page_faults;
}

// Generate a random page-reference string
void generate_page_reference_string(int page_references[], int length, int page_range) {
    for (int i = 0; i < length; i++) {
        page_references[i] = rand() % page_range;
    }
}

int main() {
    srand(time(NULL));
    int page_references[PAGE_REFERENCE_LENGTH];
    generate_page_reference_string(page_references, PAGE_REFERENCE_LENGTH, PAGE_RANGE);
    
    printf("Page reference string: ");
    for (int i = 0; i < PAGE_REFERENCE_LENGTH; i++) {
        printf("%d ", page_references[i]);
    }
    printf("\n\n");
    
    for (int num_frames = 1; num_frames <= 4; num_frames++) {
        int fifo_faults = FIFO(page_references, num_frames);
        int lru_faults = LRU(page_references, num_frames);
        
        printf("Number of frames: %d\n", num_frames);
        printf("FIFO page faults: %d\n", fifo_faults);
        printf("LRU page faults: %d\n\n", lru_faults);
    }

    return 0;
}
