#!/usr/bin/env zsh

#SBATCH -p instruction -J task6 -o task6.out -e task6.err

g++ task6.cpp -Wall -O3 -std=c++17 -o task6
./task6 6
