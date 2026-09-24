#include <chrono>
#include <ratio>
#include <iostream>
#include <random>
#include <cstdlib>
#include "scan.h"

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
  std::uniform_real_distribution<float> distrib(-1.0, 1.0);
  std::default_random_engine engine;

  // io & arr construction
  int n = std::atoi(argv[1]);
  float *arr = (float *)malloc(sizeof(float) * n);
  for (int i = 0; i < n; i ++) {
    arr[i] = distrib(engine);
  }
  float *arr_out = (float *)malloc(sizeof(float) * n);

  // time scan
  start = high_resolution_clock::now();
  scan(arr, arr_out, n);
  end = high_resolution_clock::now();

  // calculate difference
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  
  // output result
  cout << duration_ms.count() << "\n" << arr[0] << "\n" << arr[n-1] << "\n";

  // free memory
  free(arr);
  free(arr_out);
}
