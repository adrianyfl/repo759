#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task2 
#SBATCH -o task2.out 
#SBATCH -e task2.err 
#SBATCH -c 20
#SBATCH --mem=16G

g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp

for t in {1..20}
do
	echo "t = $t"
	./task2 1024 $t
done
