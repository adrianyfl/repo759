#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task2
#SBATCH -o task2.out 
#SBATCH -e task2.err
#SBATCH --gpus=1 
#SBATCH --gpus-per-task=1

module load nvidia/cuda

nvcc task2.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task2

./task2
