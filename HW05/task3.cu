#include "vscale.cuh"
#include <random>
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
    unsigned int n = std::atoi(argv[1]);

    // allocate host memory
    float* hA = new float[n];
    float* hB = new float[n];


    std::random_device rd;
    std::mt19937 gen(rd());
    // rng float values from -10.0 to 10.
    std::uniform_real_distribution<float> dista(-10.0f, 10.0f);

    // rng float values from 0.0 to 1.0
    std::uniform_real_distribution<float> distb(0.0f, 1.0f);

    // initialize host arrays
    for (unsigned int i = 0; i < n; i++) {
        hA[i] = dista(gen);
        hB[i] = distb(gen);
    }

    // allocate device memory
    float* dA;
    float* dB;
    cudaMalloc(&dA, n * sizeof(float));
    cudaMalloc(&dB, n * sizeof(float));

    // copy host arrays to device
    cudaMemcpy(dA, hA, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, n * sizeof(float), cudaMemcpyHostToDevice);

    // launch kernel with 512 threads per block
    int threadsPerBlock = 512;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    // create time
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    vscale<<<blocksPerGrid, threadsPerBlock>>>(dA, dB, n);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    // get time
    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);

    // copy result back to host
    cudaMemcpy(hB, dB, n * sizeof(float), cudaMemcpyDeviceToHost);

    // print out time, first element, and last element
    std::printf("%f\n", ms);
    std::printf("%f\n", hB[0]);
    std::printf("%f\n", hB[n - 1]);

    // clean up events
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    // free device memory
    cudaFree(dA);
    cudaFree(dB);

    // free host memory
    delete[] hA;
    delete[] hB;

}