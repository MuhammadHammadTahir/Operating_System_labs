#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep function

pthread_mutex_t alice_lock;
pthread_mutex_t bob_lock;

void* alice(void* arg) {
    printf("Alice wants Bob's phone.\n");
    pthread_mutex_lock(&alice_lock);  // Acquire Alice's lock first
    printf("Alice has Bob's phone.\n");
    sleep(1); // Introduce a delay (1 second)
    pthread_mutex_lock(&bob_lock);    // Then try to acquire Bob's lock
    printf("Alice is playing on her phone.\n");
    pthread_mutex_unlock(&bob_lock);
    pthread_mutex_unlock(&alice_lock);
    return NULL;
}

void* bob(void* arg) {
    printf("Bob wants Alice's phone.\n");
    pthread_mutex_lock(&bob_lock);    // Acquire Bob's lock first
    printf("Bob has Alice's phone.\n");
    sleep(1); // Introduce a delay (1 second)
    pthread_mutex_lock(&alice_lock);  // Then try to acquire Alice's lock
    printf("Bob is playing on his phone.\n");
    pthread_mutex_unlock(&alice_lock);
    pthread_mutex_unlock(&bob_lock);
    return NULL;
}

int main() {
    pthread_t alice_thread, bob_thread;

    pthread_mutex_init(&alice_lock, NULL);
    pthread_mutex_init(&bob_lock, NULL);

    pthread_create(&alice_thread, NULL, alice, NULL);
    pthread_create(&bob_thread, NULL, bob, NULL);

    pthread_join(alice_thread, NULL);
    pthread_join(bob_thread, NULL);

    printf("Simulation complete.\n");

    pthread_mutex_destroy(&alice_lock);
    pthread_mutex_destroy(&bob_lock);

    return 0;
}
