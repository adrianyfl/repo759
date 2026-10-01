#include <chrono>
#include <ratio>
#include <iostream>
#include <random>
#include <cstdlib>
#include "convolution.h"

// namespace shortcut
using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char**argv) {
  // clocks
  high_resolution_clock::time_point start;
  high_resolution_clock::time_point end;
  duration<double, std::milli> duration_ms;

  // rng
  std::uniform_real_distribution<float> distrib10(-10.0, 10.0);
  std::uniform_real_distribution<float> distrib1(-1.0, 1.0);
  std::default_random_engine engine;

  // io & arr construction
  std::size_t n = std::atoi(argv[1]);
  std::size_t m = std::atoi(argv[2]);
  float *img = new float[n * n];
  float *mask = new float[m * m];
  for (std::size_t i = 0; i < n * n; i ++) {
    img[i] = distrib10(engine);
  }
  for (std::size_t i = 0; i < m * m; i ++) {
    mask[i] = distrib1(engine);
  }
  float *img_out = new float[n * n];

  // time convolution
  start = high_resolution_clock::now();
  convolve(img, img_out, n, mask, m);
  end = high_resolution_clock::now();

  // calculate difference
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  
  // output result
  cout << duration_ms.count() << "\n" << img_out[0] << "\n" << img_out[n * n - 1] << "\n";

  // free memory
  delete[] img;
  delete[] img_out;
  delete[] mask;
}
