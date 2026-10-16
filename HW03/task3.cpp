#include <chrono>
#include <ratio>
#include <iostream>
#include <random>
#include <cstdlib>
#include "msort.h"

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
  std::uniform_int_distribution<int> distrib(-1000, 1000);
  std::default_random_engine engine;

  // io & arr construction
  std::size_t n = std::atoi(argv[1]);
  std::size_t t = std::atoi(argv[2]);
  std::size_t ts = std::atoi(argv[3]);
  int *arr = new int[n];
  for (std::size_t i = 0; i < n; i ++) {
    arr[i] = distrib(engine);
  }

  // set num threads
  omp_set_num_threads(t);

  // time convolution
  start = high_resolution_clock::now();
  msort(arr, n, ts);
  end = high_resolution_clock::now();

  // calculate difference
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  
  // output result
  cout << arr[0] << "\n" << arr[n - 1] << "\n" << duration_ms.count() << "\n";

  // free memory
  delete[] arr;
}
