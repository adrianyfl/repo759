#include <cuda_runtime.h>

__global__ void vscale(const float* a, float* b, unsigned int n);
