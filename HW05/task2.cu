#include <cstdio>
#include <cuda_runtime.h>
#include <random>

__global__ void kernel(int* dA, int a) {
    int x = threadIdx.x;
    int y = blockIdx.x;
    dA[y * blockDim.x + x] = a * x + y;
}

int main() {
    // generate random integers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    int a = dist(gen);
    
    // allocate N ints on the device
    const int N = 16;
    int* dA;
    cudaMalloc(&dA, N * sizeof(int));

    // launch a kernel with 2 blocks each with 8 threads
    kernel<<<2, 8>>>(dA, a);

    // copy result back
    int hA[N];
    cudaMemcpy(hA, dA, N * sizeof(int), cudaMemcpyDeviceToHost);

    // print out the 16 integers
    for (int i = 0; i < N; i++) {
        std::printf("%d ", hA[i]);
    }
    std::printf("\n");

    // free device memory
    cudaFree(dA);

    return 0;
}