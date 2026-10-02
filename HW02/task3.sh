#!/usr/bin/env zsh

#SBATCH -p instruction -J task3 -o task1.out -e task1.err

g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3 

./task3
