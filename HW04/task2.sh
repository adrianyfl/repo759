#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task2 
#SBATCH -o task2.out 
#SBATCH -e task2.err 
#SBATCH -c 8

g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 

./task2 20 20