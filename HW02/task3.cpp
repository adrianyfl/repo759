#include <chrono>
#include <ratio>
#include <iostream>
#include <random>
#include <cstdlib>
#include "matmul.h"



// namespace shortcut
using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char**argv) {
  int matrix_size = 1024*1024;
  int row_size = 1024;
  // clocks
  high_resolution_clock::time_point start;
  high_resolution_clock::time_point end;
  duration<double, std::milli> duration_ms;

  // rng
  std::uniform_real_distribution<double> distrib(-10.0, 10.0);
  std::default_random_engine gen;

  // matrix construction
  double *A  = new double[matrix_size];
  double *B  = new double[matrix_size];
  double *C  = new double[matrix_size];
  std::vector<double> A_vec;
  std::vector<double> B_vec;

  for (int i = 0; i < matrix_size; i ++) {
    A[i] = distrib(gen);
    B[i] = distrib(gen);
    A_vec.push_back(A[i]);
    B_vec.push_back(B[i]);
  }

  // run each matmul and output result  
  cout << row_size<< "\n";

  start = high_resolution_clock::now();
  mmul1(A, B, C, row_size);
  end = high_resolution_clock::now();
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  cout << duration_ms.count() << "\n" << C[matrix_size-1] << "\n";

  start = high_resolution_clock::now();
  mmul2(A, B, C, row_size);
  end = high_resolution_clock::now();
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  cout << duration_ms.count() << "\n" << C[matrix_size-1] << "\n";

  start = high_resolution_clock::now();
  mmul3(A, B, C, row_size);
  end = high_resolution_clock::now();
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  cout << duration_ms.count() << "\n" << C[matrix_size-1] << "\n";

  start = high_resolution_clock::now();
  mmul4(A_vec, B_vec, C, row_size);
  end = high_resolution_clock::now();
  duration_ms = std::chrono::duration_cast<duration<double, std::milli>> (end - start);
  cout << duration_ms.count() << "\n" << C[matrix_size-1] << "\n";

  // free memory
  delete[] A;
  delete[] B;
  delete[] C;
}
