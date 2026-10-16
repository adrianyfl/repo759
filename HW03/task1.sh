#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task1 
#SBATCH -o task1.out 
#SBATCH -e task1.err 
#SBATCH -c 20
#SBATCH --mem=16G

g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp

for t in {1..20}
do
	echo "t = $t"
	./task1 1024 $t
done
