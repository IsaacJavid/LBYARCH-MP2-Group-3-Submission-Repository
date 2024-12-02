//MP2 of Diamante, David Alexander, & Javid, Isaac
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Uncomment the following line when testing the assembly function
extern void asm_dot_product(double* A, double* B, int n);

void time_dot_product(int n, int iterations) {
    // Allocate memory for vectors A and B
    double* A = (double*)malloc(n * sizeof(double));
    double* B = (double*)malloc(n * sizeof(double));

    // Initialize vectors with random values
    for (int i = 0; i < n; i++) {
        A[i] = (rand() / (double)RAND_MAX) * 200.0 - 100.0;  // Random value between -100 and 100
        B[i] = (rand() / (double)RAND_MAX) * 200.0 - 100.0;
    }

    double total_time = 0.0;

    printf("\nC Runs\n");

    for (int iter = 0; iter < iterations; iter++) {
        double sdot = 0;
        clock_t start = clock();

        // C implementation of dot product
        for (int i = 0; i < n; i++) {
            sdot += A[i] * B[i];
        }
        printf("C Dot Product = %lf\n", sdot);

        clock_t end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }

    double avg_time = total_time / iterations;
    printf("Vector size: %d\n", n);
    printf("Average time for C implementation: %lf seconds\n", avg_time);

    // Uncomment this section to test the assembly implementation
    printf("\nAssembly Runs\n");
    
    total_time = 0.0;
    for (int iter = 0; iter < iterations; iter++) {
        clock_t start = clock();
        asm_dot_product(A, B, n);
        clock_t end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    avg_time = total_time / iterations;
    printf("Average time for Assembly implementation: %lf seconds\n", avg_time);
    

    // Free allocated memory
    free(A);
    free(B);
}

int main() {
    int iterations = 20;  // Run each test 20 times

    // Test for n = 2^20, 2^24, and 2^30 (adjust for your machine's capability)
    int sizes[] = {(int)pow(2, 20), (int)pow(2, 24), (int)pow(2, 28)};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        time_dot_product(sizes[i], iterations);
    }

    return 0;
}

