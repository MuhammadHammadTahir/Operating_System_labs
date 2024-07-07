#include <iostream>
#include <thread>
#include <chrono>
#include <list>

typedef struct process {
    int id; // For demonstration purposes
    struct process *next;
} process;

typedef struct {
    int value;
    process *list;
} semaphore;

void wait(semaphore *S, int id) {
    S->value--;
    if (S->value < 0) {
        process *new_process = new process;
        new_process->id = id;
        new_process->next = nullptr;

        if (S->list == nullptr) {
            S->list = new_process;
        } else {
            process *temp = S->list;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_process;
        }
        // block();
    }
}

void signal(semaphore *S) {
    S->value++;
    if (S->value <= 0) {
        // Remove a process from S->list
        if (S->list != nullptr) {
            process *waiting_process = S->list;
            S->list = S->list->next;
            // wakeup(waiting_process->id);
            delete waiting_process;
        }
    }
}

void reader(semaphore *mutex, semaphore *write, int id) {
    wait(mutex, id);
    std::cout << "Reader " << id << " is reading..." << std::endl;
    wait(write, id);
    signal(mutex);

    // Reading
    std::this_thread::sleep_for(std::chrono::seconds(1));

    signal(write);
}

void writer(semaphore *write, int id) {
    wait(write, id);
    std::cout << "Writer " << id << " is writing..." << std::endl;

    // Writing
    std::this_thread::sleep_for(std::chrono::seconds(1));

    signal(write);
}

void run_reader(semaphore *mutex, semaphore *write, int id) {
    while (true) {
        reader(mutex, write, id);
    }
}

void run_writer(semaphore *write, int id) {
    while (true) {
        writer(write, id);
    }
}

int main() {
    semaphore mutex, write;
    mutex.value = 1;
    mutex.list = nullptr;
    write.value = 1;
    write.list = nullptr;

    std::thread reader_thread_1(run_reader, &mutex, &write, 1);
    std::thread reader_thread_2(run_reader, &mutex, &write, 2);
    std::thread writer_thread_1(run_writer, &write, 1);
    std::thread writer_thread_2(run_writer, &write, 2);

    reader_thread_1.join();
    reader_thread_2.join();
    writer_thread_1.join();
    writer_thread_2.join();

    return 0;
}
