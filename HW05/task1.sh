#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task1
#SBATCH -o task1.out 
#SBATCH -e task1.err
#SBATCH --gpus=1 
#SBATCH --gpus-per-task=1

module load nvidia/cuda

nvcc task1.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task1

./task1
