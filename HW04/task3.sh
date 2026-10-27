#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task3
#SBATCH -o task3.out 
#SBATCH -e task3.err 
#SBATCH -c 8

g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

./task3 20 20 8