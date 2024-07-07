#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_POINTS 1000000
#define NUM_THREADS 4

int points_in_circle = 0;
pthread_mutex_t mutex;

int is_inside_circle(double x, double y) {
    return x*x + y*y <= 1;
}

void *generate_points(void *arg) {
    int i;
    int local_points_in_circle = 0;
    
    for (i = 0; i < NUM_POINTS / NUM_THREADS; i++) {
        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;
            if (is_inside_circle(x, y)) {
            local_points_in_circle++;
        }
    }

    pthread_mutex_lock(&mutex);
    points_in_circle += local_points_in_circle;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t tid[NUM_THREADS]; 
  srand(time(NULL)); 
  pthread_mutex_init(&mutex, NULL); 

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&tid[i], NULL, generate_points, NULL) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    double pi_estimate = 4.0 * points_in_circle / NUM_POINTS;
    printf("Estimated value of π: %f\n", pi_estimate);

    return EXIT_SUCCESS;
}
