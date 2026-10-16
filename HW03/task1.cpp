#include <chrono>
#include <omp.h>
#include <ratio>
#include <iostream>
#include <random>
#include "matmul.h"

// namespace shortcut
using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char**argv) {
    // input
    std::size_t n = std::atoi(argv[1]);
    std::size_t t = std::atoi(argv[2]);

    // clocks
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    // rng
    std::uniform_real_distribution<float> distrib(-10.0, 10.0);
    std::default_random_engine gen;

    // matrix construction
    float *A  = new float[n * n];
    float *B  = new float[n * n];
    float *C  = new float[n * n];

    for (std::size_t i = 0; i < n * n; i ++) {
        A[i] = distrib(gen);
        B[i] = distrib(gen);
    }

    // set number of threads for omp
    omp_set_num_threads(t);

    // run matmul and output result  
    start = high_resolution_clock::now();
    mmul(A, B, C, n);
    end = high_resolution_clock::now();
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
    cout << C[0] << "\n" << duration_ms.count() << "\n" << C[n * n -1] << "\n";

    // free memory
    delete[] A;
    delete[] B;
    delete[] C;
}