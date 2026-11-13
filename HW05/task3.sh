#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task3
#SBATCH -o task3.out 
#SBATCH -e task3.err
#SBATCH --mem=16G
#SBATCH --gpus=1 
#SBATCH --gpus-per-task=1

module load nvidia/cuda

nvcc task3.cu vscale.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task3

for p in {10..29}
do
    echo "n = 2^$p"
    ./task3 $((2**p))
done