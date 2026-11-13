#include "vscale.cuh"

__global__ void vscale(const float* a, float* b, unsigned int n) {
    // calculate index for element wise multiplication
    unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < n) {
        b[id] = a[id] * b[id];
    }
}