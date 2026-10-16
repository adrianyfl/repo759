#include "convolution.h"

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    const long N = (long)n;
    const long M = (long)m;
    const long r = (M-1) / 2;
    
    #pragma omp parallel for collapse(2)
    for (long y = 0; y < N; y ++) {
        for (long x = 0; x < N; x ++) {
        // for each g[x,y]
        float temp = 0;

        if (x >= r && x + r < N && y >= r && y + r < N) {
            // no bound checks needed for simd
            for (long j = 0; j < M; j ++) {
                long img_y = y + j - r;
                #pragma omp simd reduction(+:temp)
                for (long i = 0; i < M; i ++) {
                    // image coordinate to access
                    long img_x = x + i - r;
                    temp += *(mask + j * M + i) * *(image + img_y * N + img_x);
                }
            }
        } else {
            for (long j = 0; j < M; j ++) {
                long img_y = y + j - r;
                for (long i = 0; i < M; i ++) {
                    // image coordinate to access
                    long img_x = x + i - r;
                    // check for corner/edge
                    if (0 <= img_x && img_x < N && 0 <= img_y && img_y < N) 
                        temp += *(mask + j * M + i) * *(image + img_y * N + img_x);
                    else if ((img_x < 0 || img_x >= N) && (img_y < 0 || img_y >= N))
                        continue;
                    else
                        temp += *(mask + j * M + i);
                }
            }
        }
        
        *(output + y * N + x) = temp;
        }
    }
}

