#include <cstdlib>
#include <cstdio>
#include <iostream>

int main (int argc, char *argv[]) {
  int N = std::atoi(argv[1]); 
  for (int i = 0; i <= N; i++) {
    printf("%i ", i);
  }
  printf("\n");
  for (int i = N; i >= 0; i --) {
    std::cout << i << " ";
  }
  printf("\n");
  return 0;
}
