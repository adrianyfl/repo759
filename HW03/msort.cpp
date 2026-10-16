#include "msort.h"
#include <algorithm>

void msort_recurse(int* arr, int* tmp, const std::size_t n, const std::size_t threshold);
void merge(int* arr, int* tmp, const long mid, const long n);

void msort(int* arr, const std::size_t n, const std::size_t threshold) {
    int* tmp = new int[n];

    #pragma omp parallel
    #pragma omp single
    msort_recurse(arr, tmp, n, threshold);

    delete[] tmp;
}


void msort_recurse(int* arr, int* tmp, const std::size_t n, const std::size_t threshold) {
    if (n <= threshold){
        // sort
        std::sort(arr, arr + n);
        return;
    }
    
    long mid = n/2;

    // left side
    #pragma omp task
    msort_recurse(arr, tmp, mid, threshold);

    // right side
    #pragma omp task
    msort_recurse(arr + mid, tmp + mid, n - mid, threshold);

    // merge
    #pragma omp taskwait
    merge(arr, tmp, mid, n);
}

void merge(int* arr, int* tmp, const long mid, const long n) {
    long left = 0;
    long right = mid;
    long tmp_i = 0;

    // until one arr is done
    while (left < mid && right < n) {
        if (arr[left] <= arr[right]) tmp[tmp_i++] = arr[left++];
        else tmp[tmp_i ++] = arr[right++];
    }

    // remaining left
    while (left < mid) tmp[tmp_i++] = arr[left++];

    // remaining right
    while (right < n) tmp[tmp_i++] = arr[right++];

    // copy back to arr
    std::copy(tmp, tmp+n, arr);
}