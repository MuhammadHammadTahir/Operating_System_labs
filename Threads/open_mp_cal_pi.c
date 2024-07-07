#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_POINTS 1000000 

int main() {
    int points_in_circle = 0; // Variable to store the count of points in the circle

    srand(time(NULL)); // Seed the random number generator

    // Use OpenMP to parallelize the generation of random points
    #pragma omp parallel for reduction(+:points_in_circle)
    for (int i = 0; i < NUM_POINTS; i++) {
        // Generate random (x, y) coordinates within the square [-1, 1] x [-1, 1]
        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;

        // Check if the point falls within the circle
        if (x*x + y*y <= 1) {
            points_in_circle++;
        }
    }

    // Estimate π using the Monte Carlo method
    double pi_estimate = 4.0 * points_in_circle / NUM_POINTS;

    // Output the estimated value of π
    printf("Estimated value of π: %f\n", pi_estimate);

    return EXIT_SUCCESS;
}
