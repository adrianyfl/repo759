#!/usr/bin/env zsh

#SBATCH -p instruction -J task1 -o task1.out -e task1.err 

g++ scan.cpp task1.cpp -Wall -O3 -std=c++17 -o task1

for n in {10..30} do
  ./task1 $((2**n))
done
