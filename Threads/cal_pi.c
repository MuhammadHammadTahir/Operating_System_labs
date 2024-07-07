#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_POINTS 1000000 

int points_in_circle = 0; 

// Function to check if a point (x, y) falls within the circle
int is_inside_circle(double x, double y) {
    return x*x + y*y <= 1;
}

void *generate_points(void *arg) {
    int i;
    int local_points_in_circle = 0;
    
    for (i = 0; i < NUM_POINTS; i++) {
        // Generate random (x, y) coordinates within the square [-1, 1] x [-1, 1]
        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;

        // Check if the point falls within the circle
        if (is_inside_circle(x, y)) {
            local_points_in_circle++;
        }
    }

    // Update the global count of points in the circle
    points_in_circle += local_points_in_circle;

    pthread_exit(NULL);
}

int main() {
    pthread_t tid; // Thread ID
    srand(time(NULL)); // Seed the random number generator

    // Create a thread to generate random points
    if (pthread_create(&tid, NULL, generate_points, NULL) != 0) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    // Wait for the thread to finish
    pthread_join(tid, NULL);

    // Estimate π using the Monte Carlo method
    double pi_estimate = 4.0 * points_in_circle / NUM_POINTS;

    // Output the estimated value of π
    printf("Estimated value of π: %f\n", pi_estimate);

    return EXIT_SUCCESS;
}
