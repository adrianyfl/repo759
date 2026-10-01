#include "convolution.h"

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
  for (std::size_t y = 0; y < n; y ++) {
    for (std::size_t x = 0; x < n; x ++) {
      // for each g[x,y]
      float temp = 0;
      for (std::size_t j = 0; j < m; j ++) {
        for (std::size_t i = 0; i < m; i ++) {
          // image coordinate to access
          std::size_t img_x = x + i - (m-1) / 2;
          std::size_t img_y = y + j - (m-1) / 2;
          // check for corner/edge
          if (0 <= img_x && img_x < n && 0 <= img_y && img_y < n) 
            temp += *(mask + j * m + i) * *(image + img_y * n + img_x);
          else if ((img_x < 0 || img_x >= n) && (img_y < 0 || img_y >= n))
            continue;
          else
            temp += *(mask + j * m + i);
        }
      }
      *(output + y * n + x) = temp;
    }
  }
}

